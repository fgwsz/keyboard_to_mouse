#include <iostream>
#include <windows.h>
// 模拟鼠标左键单击
void MouseLeftClick() {
    ::std::cout<<__func__<<::std::endl;
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
    input.mi.dx = 0; // 鼠标dx坐标
    input.mi.dy = 0; // 鼠标dy坐标
    input.mi.mouseData = 0;
    input.mi.dwExtraInfo = 0;
    input.mi.time = 0;
    SendInput(1, &input, sizeof(INPUT));
}
// 模拟鼠标左键双击
void MouseLeftDoubleClick() {
    MouseLeftClick();
    MouseLeftClick();
}
// 模拟鼠标右键单击
void MouseRightClick() {
    ::std::cout<<__func__<<::std::endl;
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP;
    input.mi.dx = 0; // 鼠标dx坐标
    input.mi.dy = 0; // 鼠标dy坐标
    input.mi.mouseData = 0;
    input.mi.dwExtraInfo = 0;
    input.mi.time = 0;
    SendInput(1, &input, sizeof(INPUT));
}
// 模拟鼠标向上移动
void MouseMoveUp(){
    ::std::cout<<__func__<<::std::endl;
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    SetCursorPos(cursorPos.x, cursorPos.y - 10);
    ::std::cout<<"current cursor pos:"<<cursorPos.x<<","<<cursorPos.y<<::std::endl;
}
// 模拟鼠标向下移动
void MouseMoveDown(){
    ::std::cout<<__func__<<::std::endl;
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    SetCursorPos(cursorPos.x, cursorPos.y + 10);
    ::std::cout<<"current cursor pos:"<<cursorPos.x<<","<<cursorPos.y<<::std::endl;
}
// 模拟鼠标向左移动
void MouseMoveLeft(){
    ::std::cout<<__func__<<::std::endl;
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    SetCursorPos(cursorPos.x - 10, cursorPos.y);
    ::std::cout<<"current cursor pos:"<<cursorPos.x<<","<<cursorPos.y<<::std::endl;
}
// 模拟鼠标向右移动
void MouseMoveRight(){
    ::std::cout<<__func__<<::std::endl;
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    SetCursorPos(cursorPos.x + 10, cursorPos.y);
    ::std::cout<<"current cursor pos:"<<cursorPos.x<<","<<cursorPos.y<<::std::endl;
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
            ::std::cout<<"key down:"<<pKeyData->vkCode<<::std::endl;
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
            ::std::cout<<"key up:"<<pKeyData->vkCode<<::std::endl;
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
