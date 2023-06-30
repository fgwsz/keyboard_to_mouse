#include<iostream>
#include<windows.h>
#include<type_traits>
#include<string>
#include<unordered_map>
class Logger{
    bool is_debug_;
    ::std::string head_;
public:
    Logger(bool is_debug=true)
        :is_debug_(is_debug)
        ,head_("")
    {
        ::std::cout<<::std::unitbuf;// 设置无缓冲区输出
    }
    Logger& setDebug(){ 
        this->is_debug_=true;
        return *this;
    }
    Logger& setRelease(){
        this->is_debug_=false;
        return *this;
    }
    Logger& setHead(::std::string const& head){
        this->head_=head;
        return *this;
    }
private:
    Logger& _println(){
        if(this->is_debug_){
            ::std::cout<<::std::endl;
        }
        return *this;
    }
    template<typename _Type,typename..._Types>
    Logger& _println(_Type&& arg,_Types&&...args){
        if(this->is_debug_){
            ::std::cout<<::std::forward<_Type>(arg);
        }
        if constexpr(sizeof...(args)!=0){
            this->_println(::std::forward<_Types>(args)...);
        }else{
            this->_println();
        }
        return *this;
    }
public:
    template<typename..._Types>
    Logger& println(_Types&&...args){
        if(this->is_debug_){
            ::std::cout<<this->head_;
        }
        return this->_println(::std::forward<_Types>(args)...);
    }
};
static Logger keyboard_logger;
static Logger mouse_logger;
void _mouseClick(DWORD dw_flags){
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
void mouseLeftClick() {
    mouse_logger.println("MOUSE LEFT CLICK");
    _mouseClick(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP);
}
// 模拟鼠标左键双击
void mouseLeftDoubleClick() {
    mouseLeftClick();
    mouseLeftClick();
}
// 模拟鼠标右键单击
void mouseRightClick() {
    mouse_logger.println("MOUSE RIGHT CLICK");
    _mouseClick(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP);
}
void _mouseMove(LONG dx,LONG dy){
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    SetCursorPos(cursorPos.x+dx, cursorPos.y+dy);
    mouse_logger.println("CURSOR POS(",cursorPos.x,",",cursorPos.y,")");
}
// 模拟鼠标向上移动
void mouseMoveUp(){
    mouse_logger.println("MOUSE MOVE UP");
    _mouseMove(0,-10);
}
// 模拟鼠标向下移动
void mouseMoveDown(){
    mouse_logger.println("MOUSE MOVE DOWN");
    _mouseMove(0,10);
}
// 模拟鼠标向左移动
void mouseMoveLeft(){
    mouse_logger.println("MOUSE MOVE LEFT");
    _mouseMove(-10,0);
}
// 模拟鼠标向右移动
void mouseMoveRight(){
    mouse_logger.println("MOUSE MOVE RIGHT");
    _mouseMove(10,0);
}
void _mouseWheel(DWORD scroll_amount){
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    input.mi.mouseData = scroll_amount;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;
    SendInput(1, &input, sizeof(INPUT));
}
// 模拟鼠标滚轮向上滑动
void mouseWheelUp(){
    mouse_logger.println("MOUSE WHEEL UP");
    _mouseWheel(10);
}
// 模拟鼠标滚轮向下滑动
void mouseWheelDown(){
    mouse_logger.println("MOUSE WHEEL DOWN");
    _mouseWheel(-10);
}
static ::std::unordered_map<DWORD,::std::string> keycode_to_string;
static auto emplace=[](auto& map,::std::string const& key_name,DWORD key_code){
    map.emplace(key_code,
        ::std::string{"<"}
            .append(key_name)
            .append(">{")
            .append(::std::to_string(key_code))
            .append("}")
    );
};
bool _initkeycodeToString(){
    for(DWORD key_code='A';key_code<='Z';++key_code){
        emplace(keycode_to_string,::std::string(1,key_code),key_code);
    }
    for(DWORD key_code='0';key_code<='9';++key_code){
        emplace(keycode_to_string,::std::string(1,key_code),key_code);
    }
    emplace(keycode_to_string,"Left Shift" ,160);
    emplace(keycode_to_string,"Right Shfit",161);
    emplace(keycode_to_string,"Left Ctrl"  ,162);
    emplace(keycode_to_string,"Right Ctrl" ,163);
    emplace(keycode_to_string,"Left Alt"   ,164);
    emplace(keycode_to_string,"Right Alt"  ,165);
    emplace(keycode_to_string,"Esc"        ,27 );
    emplace(keycode_to_string,"Tab"        ,9  );
    emplace(keycode_to_string,"Backspace"  ,8  );
    emplace(keycode_to_string,"Enter"      ,13 );
    emplace(keycode_to_string,"CapsLk"     ,20 );
    emplace(keycode_to_string,"Application",93 );
    emplace(keycode_to_string,"Space"      ,32 );
    emplace(keycode_to_string,"Up"         ,38 );
    emplace(keycode_to_string,"Down"       ,40 );
    emplace(keycode_to_string,"Left"       ,37 );
    emplace(keycode_to_string,"Right"      ,39 );
    emplace(keycode_to_string,"Win"        ,91 );
    emplace(keycode_to_string,"F1"         ,112);
    emplace(keycode_to_string,"F2"         ,113);
    emplace(keycode_to_string,"F3"         ,114);
    emplace(keycode_to_string,"F4"         ,115);
    emplace(keycode_to_string,"F5"         ,116);
    emplace(keycode_to_string,"F6"         ,117);
    emplace(keycode_to_string,"F7"         ,118);
    emplace(keycode_to_string,"F8"         ,119);
    emplace(keycode_to_string,"F9"         ,120);
    emplace(keycode_to_string,"F10"        ,121);
    emplace(keycode_to_string,"-"          ,189);
    emplace(keycode_to_string,"="          ,187);
    emplace(keycode_to_string,"["          ,219);
    emplace(keycode_to_string,"]"          ,221);
    emplace(keycode_to_string,"|"          ,220);
    emplace(keycode_to_string,";"          ,186);
    emplace(keycode_to_string,"\'"         ,222);
    emplace(keycode_to_string,","          ,188);
    emplace(keycode_to_string,"."          ,190);
    emplace(keycode_to_string,"/"          ,191);
    return true;
}
static bool init_keycode_to_string=_initkeycodeToString();
::std::string& keycodeToString(DWORD key_code){
    if(keycode_to_string.count(key_code)==0){
        emplace(keycode_to_string,::std::to_string(key_code),key_code);
    }
    return keycode_to_string.at(key_code);
}
// 全局键盘钩子回调函数
LRESULT CALLBACK keyboardProc(int n_code, WPARAM w_param, LPARAM l_param) {
    static constexpr DWORD leader_keycode=164;//left alt
    static bool is_leader_down=false;
    if (n_code == HC_ACTION) {
        KBDLLHOOKSTRUCT* p_key_data = (KBDLLHOOKSTRUCT*)l_param;
        // 检查按下的键
        if (w_param == WM_KEYDOWN || w_param == WM_SYSKEYDOWN) {
            keyboard_logger.println(keycodeToString(p_key_data->vkCode)," KEY DOWN");
            if(p_key_data->vkCode==leader_keycode){ is_leader_down=true;}
            else if(is_leader_down&&p_key_data->vkCode=='H'/*vim h*/){ mouseMoveLeft() ; }
            else if(is_leader_down&&p_key_data->vkCode=='J'/*vim j*/){ mouseMoveDown() ; }
            else if(is_leader_down&&p_key_data->vkCode=='K'/*vim k*/){ mouseMoveUp()   ; }
            else if(is_leader_down&&p_key_data->vkCode=='L'/*vim l*/){ mouseMoveRight(); }
            else if(is_leader_down&&p_key_data->vkCode=='O'/*gba o*/){ mouseLeftClick(); }
            else if(is_leader_down&&p_key_data->vkCode=='A'/*gba a*/){ mouseLeftDoubleClick(); }
            else if(is_leader_down&&p_key_data->vkCode=='X'/*gba x*/){ mouseRightClick(); }
            else if(is_leader_down&&p_key_data->vkCode=='B'/*back */){ mouseWheelUp()   ; }
            else if(is_leader_down&&p_key_data->vkCode=='N'/*next */){ mouseWheelDown() ; }
        }
        // 检查松开的键盘
        if (w_param == WM_KEYUP || w_param == WM_SYSKEYUP) {
            keyboard_logger.println(keycodeToString(p_key_data->vkCode)," KEY UP");
            if(p_key_data->vkCode==leader_keycode){ is_leader_down=false;}
        }
    }
    return CallNextHookEx(NULL, n_code, w_param, l_param);
}
#ifndef DEBUG
//不显示控制台
#pragma comment(linker,"/subsystem:windows /entry:mainCRTStartup")
#endif
int main() {
    mouse_logger.setHead("[MOU] ");
    keyboard_logger.setHead("[KEY] ");
#ifndef DEBUG
    mouse_logger.setRelease();
    keyboard_logger.setRelease();
#else
    mouse_logger.setDebug();
    keyboard_logger.setDebug();
#endif
    // 安装全局键盘钩子
    HHOOK h_hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);
    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    // 卸载全局钩子
    UnhookWindowsHookEx(h_hook);
    return 0;
}
