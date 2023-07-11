#include"logger.h"
#include"mouse.h"
#include"keyboard.h"

//用于测试的开关
#define DEBUG

#ifdef DEBUG
//显示打印信息
static bool logger_global_enable=[]{
    Logger::setGlobalEnable(true);
    return true;
}();
#else
//不显示控制台窗口
#pragma comment(linker,"/subsystem:windows /entry:mainCRTStartup")
//不显示打印信息
static bool logger_global_enable=[]{
    Logger::setGlobalEnable(false);
    return false;
}();
#endif

static Logger mouse_logger(true,"[MOU] ");
static Logger keyboard_logger(true,"[KEY] ");
static Logger app_logger(true,"[APP] ");
static Logger hook_logger(true,"[HOO] " );

// 全局键盘钩子回调函数
static LRESULT CALLBACK _keyBoardCallBack(int n_code, WPARAM w_param, LPARAM l_param);

// 全局钩子外覆类
class Hook final{
    HHOOK h_hook_;
public:
    Hook(HHOOK h_hook):h_hook_(h_hook){
        if(this->h_hook_){
            hook_logger.println("HOOK INSTALL OK");
        }else{
            hook_logger.println("HOOK INSTALL ERROR");
            exit(1);
        }
    }
    // 析构时自动卸载全局钩子
    ~Hook(){
        if(this->h_hook_&&UnhookWindowsHookEx(this->h_hook_)){
            hook_logger.println("HOOK UNINSTALL OK");
        }else{
            hook_logger.println("HOOK UNINSTALL ERROR");
        }
    }
};

// 安装全局键盘钩子
static Hook h_hook={SetWindowsHookEx(WH_KEYBOARD_LL, _keyBoardCallBack, NULL, 0)};
// 设置为静态变量而不设置为main函数局部变量的原因：
// 在进程结束时自动回收静态变量，从而调用析构函数卸载全局钩子

int main() {
    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

// 快捷键设置
struct KeyCodeOf{
static constexpr DWORD leader                 =KeyCode_LeftAlt;
static constexpr DWORD mouse_move_up          =KeyCode_K      ;// Vim K
static constexpr DWORD mouse_move_down        =KeyCode_J      ;// Vim J
static constexpr DWORD mouse_move_left        =KeyCode_H      ;// Vim H
static constexpr DWORD mouse_move_right       =KeyCode_L      ;// Vim L
static constexpr DWORD mouse_wheel_up         =KeyCode_B      ;// Back
static constexpr DWORD mouse_wheel_down       =KeyCode_N      ;// Next
static constexpr DWORD mouse_left_click       =KeyCode_O      ;// GameBoy O
static constexpr DWORD mouse_left_double_click=KeyCode_A      ;// GameBoy A
static constexpr DWORD mouse_right_click      =KeyCode_X      ;// GameBoy X
static constexpr DWORD mouse_key_up           =KeyCode_U      ;// Up or Undo
static constexpr DWORD mouse_left_down        =KeyCode_G      ;// Get
static constexpr DWORD mouse_right_down       =KeyCode_I      ;// Invert
static constexpr DWORD mouse_dpixel_double    =KeyCode_2      ;// * 2
static constexpr DWORD mouse_dpixel_halve     =KeyCode_Hyphen ;// - Decrease
static constexpr DWORD app_quit               =KeyCode_Q      ;// Quit
};

static LRESULT CALLBACK _keyBoardCallBack(int n_code, WPARAM w_param, LPARAM l_param) {
    static bool is_leader_down=false;
    static bool is_mouse_left_down=false;
    static bool is_mouse_right_down=false;
    static Mouse::Position mouse_position={};
    static auto println_mouse_position_before_move=[&]{
        Mouse::mousePosition(mouse_position);
        mouse_logger.println(
            "MOUSE MOVE BEFORE POSITION(",
            mouse_position.x,",",
            mouse_position.y,")"
        );
    };
    static auto println_mouse_position_after_move=[&]{
        Mouse::mousePosition(mouse_position);
        mouse_logger.println(
            "MOUSE MOVE AFTER  POSITION(",
            mouse_position.x,",",
            mouse_position.y,")"
        );
    };
    static auto mouse_key_auto_up=[&]{
        if(is_mouse_left_down){
            mouse_logger.println("MOUSE LEFT UP");
            Mouse::mouseLeftUp();
            is_mouse_left_down=false;
        }else if(is_mouse_right_down){
            mouse_logger.println("MOUSE RIGHT UP");
            Mouse::mouseRightUp();
            is_mouse_right_down=false;
        }
    };
    static KBDLLHOOKSTRUCT* p_key_data=nullptr;
    if (n_code == HC_ACTION) {
        p_key_data = (KBDLLHOOKSTRUCT*)l_param;
        // 检查按下的键
        if (w_param == WM_KEYDOWN || w_param == WM_SYSKEYDOWN) {
            // 打印按键信息
            keyboard_logger.println(
                "<",KeyBoard::keyCodeToName(p_key_data->vkCode),">",
                "{",p_key_data->vkCode,"}",
                " KEY DOWN"
            );
            // 更新leader键标识位
            if(p_key_data->vkCode==KeyCodeOf::leader){
                is_leader_down=true;
            }
            // 检查leader键是否处于按下状态，若处于按下状态，则继续
            else if(!is_leader_down){}
            // <leader mouse_move_left>按下时 鼠标左移
            else if(p_key_data->vkCode==KeyCodeOf::mouse_move_left){ 
                mouse_logger.println("MOUSE MOVE LEFT");
                println_mouse_position_before_move();
                Mouse::mouseMoveLeft();
                println_mouse_position_after_move();
            }
            // <leader mouse_move_down>按下时 鼠标下移
            else if(p_key_data->vkCode==KeyCodeOf::mouse_move_down){
                mouse_logger.println("MOUSE MOVE DOWN");
                println_mouse_position_before_move();
                Mouse::mouseMoveDown();
                Mouse::mousePosition(mouse_position);
                println_mouse_position_after_move();
            }
            // <leader mouse_move_up>按下时 鼠标上移
            else if(p_key_data->vkCode==KeyCodeOf::mouse_move_up){
                mouse_logger.println("MOUSE MOVE UP");
                println_mouse_position_before_move();
                Mouse::mouseMoveUp();
                println_mouse_position_after_move();
            }
            // <leader mouse_move_right>按下时 鼠标右移
            else if(p_key_data->vkCode==KeyCodeOf::mouse_move_right){
                mouse_logger.println("MOUSE MOVE RIGHT");
                println_mouse_position_before_move();
                Mouse::mouseMoveRight();
                println_mouse_position_after_move();
            }
            // <leader mouse_wheel_up>按下时 鼠标滚轮上滑
            else if(p_key_data->vkCode==KeyCodeOf::mouse_wheel_up){
                mouse_logger.println("MOUSE WHEEL UP");
                Mouse::mouseWheelUp();
            }
            // <leader mouse_wheel_down>按下时 鼠标滚轮下滑
            else if(p_key_data->vkCode==KeyCodeOf::mouse_wheel_down){
                mouse_logger.println("MOUSE WHEEL DOWN");
                Mouse::mouseWheelDown();
            }
            // <leader app_quit>按下时 程序退出
            else if(p_key_data->vkCode==KeyCodeOf::app_quit){
                app_logger.println("APP QUIT");
                exit(0);
            }
            // <leader mouse_dpixel_double>按下时 鼠标移动/滚轮滑动距离翻倍
            else if(p_key_data->vkCode==KeyCodeOf::mouse_dpixel_double){
                mouse_logger.println("MOUSE D_PIXEL * 2");
                mouse_logger.println("MOUSE D_PIXEL BEFORE IS ",Mouse::current_dpixel_);
                Mouse::current_dpixel_=Mouse::current_dpixel_*2;
                mouse_logger.println("MOUSE D_PIXEL AFTER  IS ",Mouse::current_dpixel_);
            }
            // <leader mouse_dpixel_halve>按下时 鼠标移动/滚轮滑动距离减半
            else if(p_key_data->vkCode==KeyCodeOf::mouse_dpixel_halve){
                mouse_logger.println("MOUSE D_PIXEL / 2");
                mouse_logger.println("MOUSE D_PIXEL BEFORE IS ",Mouse::current_dpixel_);
                Mouse::current_dpixel_=Mouse::current_dpixel_/2==0
                    ?1
                    :Mouse::current_dpixel_/2
                ;
                mouse_logger.println("MOUSE D_PIXEL AFTER  IS ",Mouse::current_dpixel_);
            }
            // <leader mouse_key_up>按下时(鼠标左/右键按下时) 鼠标左/右键松开
            else if(p_key_data->vkCode==KeyCodeOf::mouse_key_up){
                mouse_key_auto_up();
            }
            // <leader mouse_left_click>按下时 鼠标左键单击
            else if(p_key_data->vkCode==KeyCodeOf::mouse_left_click){
                mouse_key_auto_up();
                mouse_logger.println("MOUSE LEFT CLICK");
                Mouse::mouseLeftClick();
            }
            // <leader mouse_left_double_click>按下时 鼠标左键双击
            else if(p_key_data->vkCode==KeyCodeOf::mouse_left_double_click){
                mouse_key_auto_up();
                mouse_logger.println("MOUSE LEFT DOUBLE CLICK");
                Mouse::mouseLeftDoubleClick();
            }
            // <leader mouse_right_click>按下时 鼠标右键单击
            else if(p_key_data->vkCode==KeyCodeOf::mouse_right_click){
                mouse_key_auto_up();
                mouse_logger.println("MOUSE RIGHT CLICK");
                Mouse::mouseRightClick();
            }
            // <leader mouse_left_down>按下时 鼠标左键按下
            else if(p_key_data->vkCode==KeyCodeOf::mouse_left_down){
                mouse_key_auto_up();
                mouse_logger.println("MOUSE LEFT DOWN");
                Mouse::mouseLeftDown();
                is_mouse_left_down=true;
            }
            // <leader mouse_right_down>按下时 鼠标右键按下
            else if(p_key_data->vkCode==KeyCodeOf::mouse_right_down){
                mouse_key_auto_up();
                mouse_logger.println("MOUSE RIGHT DOWN");
                Mouse::mouseRightDown();
                is_mouse_right_down=true;
            }
        }
        // 检查松开的键盘
        else if (w_param == WM_KEYUP || w_param == WM_SYSKEYUP) {
            // 打印按键信息
            keyboard_logger.println(
                "<",KeyBoard::keyCodeToName(p_key_data->vkCode),">",
                "{",p_key_data->vkCode,"}",
                " KEY UP"
            );
            // 更新leader键标识位
            if(p_key_data->vkCode==KeyCodeOf::leader){
                is_leader_down=false;
            }
        }
    }
    return CallNextHookEx(NULL, n_code, w_param, l_param);
}
