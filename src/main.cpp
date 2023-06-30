#include <iostream>
#include <windows.h>
#include <type_traits>
class Logger{
    bool is_debug_;
public:
    Logger(bool is_debug=true):is_debug_(is_debug){}
    Logger& setDebug(){this->is_debug_=true;}
    Logger& setRelease(){this->is_debug_=false;}
    Logger& println(){
        if(this->is_debug_){
            ::std::cout<<::std::endl;
        }
        return *this;
    }
    template<typename _Type,typename..._Types>
    Logger& println(_Type&& arg,_Types&&...args){
        if(this->is_debug_){
            ::std::cout<<::std::forward<_Type>(arg);
        }
        if constexpr(sizeof...(args)!=0){
            this->println(::std::forward<_Types>(args)...);
        }else{
            this->println();
        }
        return *this;
    }
};
static Logger logger(false);
void _MouseClick(DWORD dw_flags){
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = dw_flags;
    input.mi.dx = 0;
    input.mi.dy = 0;
    input.mi.mouseData = 0;
    input.mi.dwExtraInfo = 0;
    input.mi.time = 0;
    SendInput(1, &input, sizeof(INPUT));
}
// 模拟鼠标左键单击
void MouseLeftClick() {
    logger.println(__func__);
    _MouseClick(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP);
}
// 模拟鼠标左键双击
void MouseLeftDoubleClick() {
    MouseLeftClick();
    MouseLeftClick();
}
// 模拟鼠标右键单击
void MouseRightClick() {
    logger.println(__func__);
    _MouseClick(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP);
}
void _MouseMove(LONG dx,LONG dy){
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    SetCursorPos(cursorPos.x+dx, cursorPos.y+dy);
    logger.println("current cursor pos:",cursorPos.x,",",cursorPos.y);
}
// 模拟鼠标向上移动
void MouseMoveUp(){
    logger.println(__func__);
    _MouseMove(0,-10);
}
// 模拟鼠标向下移动
void MouseMoveDown(){
    logger.println(__func__);
    _MouseMove(0,10);
}
// 模拟鼠标向左移动
void MouseMoveLeft(){
    logger.println(__func__);
    _MouseMove(-10,0);
}
// 模拟鼠标向右移动
void MouseMoveRight(){
    logger.println(__func__);
    _MouseMove(10,0);
}
// 全局键盘钩子回调函数
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    static constexpr DWORD leader_keycode=164;//Alt
    static bool is_leader_down=false;
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyData = (KBDLLHOOKSTRUCT*)lParam;
        // 检查按下的键
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            // 处理你感兴趣的按键
            logger.println("key down:",pKeyData->vkCode);
            if(pKeyData->vkCode==leader_keycode){ is_leader_down=true;}
            else if(is_leader_down&&pKeyData->vkCode=='H'){ MouseMoveLeft() ; }
            else if(is_leader_down&&pKeyData->vkCode=='J'){ MouseMoveDown() ; }
            else if(is_leader_down&&pKeyData->vkCode=='K'){ MouseMoveUp()   ; }
            else if(is_leader_down&&pKeyData->vkCode=='L'){ MouseMoveRight(); }
            else if(is_leader_down&&pKeyData->vkCode=='O'){ MouseLeftClick(); }
            else if(is_leader_down&&pKeyData->vkCode=='A'){ MouseLeftDoubleClick(); }
            else if(is_leader_down&&pKeyData->vkCode=='X'){ MouseRightClick(); }
        }
        // 检查松开的键盘
        if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
            // 处理你感兴趣的按键
            logger.println("key up:",pKeyData->vkCode);
            if(pKeyData->vkCode==leader_keycode){ is_leader_down=false;}
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
int main() {
    // 安装全局键盘钩子
    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    // 卸载全局钩子
    UnhookWindowsHookEx(hHook);
    return 0;
}
