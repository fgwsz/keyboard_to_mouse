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
static Logger exe_logger(true,"[EXE] ");
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

static LRESULT CALLBACK _keyBoardCallBack(int n_code, WPARAM w_param, LPARAM l_param) {
    static constexpr DWORD leader_keycode=164;/*key code of `LeftAlt`*/
    static bool is_leader_down=false;
    static bool is_mouse_left_down=false;
    static bool is_mouse_right_down=false;
    static Mouse::Position mouse_position={};
    static auto println_mouse_position_before_move=[&](){
        Mouse::mousePosition(mouse_position);
        mouse_logger.println(
            "MOUSE MOVE BEFORE POSITION(",
            mouse_position.x,",",
            mouse_position.y,")"
        );
    };
    static auto println_mouse_position_after_move=[&](){
        Mouse::mousePosition(mouse_position);
        mouse_logger.println(
            "MOUSE MOVE AFTER  POSITION(",
            mouse_position.x,",",
            mouse_position.y,")"
        );
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
            if(p_key_data->vkCode==leader_keycode){
                is_leader_down=true;
            }
            // 检查leader键是否处于按下状态，若处于按下状态，则继续
            else if(!is_leader_down){}
            // <leader h>按下时 鼠标左移
            else if(p_key_data->vkCode=='H'/*vim h*/){ 
                mouse_logger.println("MOUSE MOVE LEFT");
                println_mouse_position_before_move();
                Mouse::mouseMoveLeft();
                println_mouse_position_after_move();
            }
            // <leader j>按下时 鼠标下移
            else if(p_key_data->vkCode=='J'/*vim j*/){
                mouse_logger.println("MOUSE MOVE DOWN");
                println_mouse_position_before_move();
                Mouse::mouseMoveDown();
                Mouse::mousePosition(mouse_position);
                println_mouse_position_after_move();
            }
            // <leader k>按下时 鼠标上移
            else if(p_key_data->vkCode=='K'/*vim k*/){
                mouse_logger.println("MOUSE MOVE UP");
                println_mouse_position_before_move();
                Mouse::mouseMoveUp();
                println_mouse_position_after_move();
            }
            // <leader l>按下时 鼠标右移
            else if(p_key_data->vkCode=='L'/*vim l*/){
                mouse_logger.println("MOUSE MOVE RIGHT");
                println_mouse_position_before_move();
                Mouse::mouseMoveRight();
                println_mouse_position_after_move();
            }
            // <leader b>按下时 鼠标滚轮上滑
            else if(p_key_data->vkCode=='B'/*back*/){
                mouse_logger.println("MOUSE WHEEL UP");
                Mouse::mouseWheelUp();
            }
            // <leader n>按下时 鼠标滚轮下滑
            else if(p_key_data->vkCode=='N'/*next*/){
                mouse_logger.println("MOUSE WHEEL DOWN");
                Mouse::mouseWheelDown();
            }
            // <leader q>按下时 程序退出
            else if(p_key_data->vkCode=='Q'/*quit*/){
                exe_logger.println("EXE QUIT");
                exit(0);
            }
            // <leader 2>按下时 鼠标移动/滚轮滑动距离翻倍
            else if(p_key_data->vkCode=='2'){
                mouse_logger.println("MOUSE D_PIXEL * 2");
                mouse_logger.println("MOUSE D_PIXEL BEFORE IS ",Mouse::current_dpixel_);
                Mouse::current_dpixel_=Mouse::current_dpixel_*2;
                mouse_logger.println("MOUSE D_PIXEL AFTER  IS ",Mouse::current_dpixel_);
            }
            // <leader ->按下时 鼠标移动/滚轮滑动距离减半
            else if(p_key_data->vkCode==189/*key code of `-`*/){
                mouse_logger.println("MOUSE D_PIXEL / 2");
                mouse_logger.println("MOUSE D_PIXEL BEFORE IS ",Mouse::current_dpixel_);
                Mouse::current_dpixel_=Mouse::current_dpixel_/2==0
                    ?1
                    :Mouse::current_dpixel_/2
                ;
                mouse_logger.println("MOUSE D_PIXEL AFTER  IS ",Mouse::current_dpixel_);
            }
            // 鼠标左右键至少有一个处于按下状态时，若都不处于按下状态，则继续
            else if(is_mouse_left_down||is_mouse_right_down){
                // <leader u>按下时(鼠标左右键按下时) 鼠标左/右键松开
                if(p_key_data->vkCode=='U'/*un select*/){
                    if(is_mouse_left_down){
                        mouse_logger.println("MOUSE LEFT UP");
                        Mouse::mouseLeftUp();
                        is_mouse_left_down=false;
                    }else{
                        mouse_logger.println("MOUSE RIGHT UP");
                        Mouse::mouseRightUp();
                        is_mouse_right_down=false;
                    }
                }
            }
            // <leader o>按下时(鼠标左右键没有按下时) 鼠标左键单击
            else if(p_key_data->vkCode=='O'/*gba o*/){
                mouse_logger.println("MOUSE LEFT CLICK");
                Mouse::mouseLeftClick();
            }
            // <leader a>按下时(鼠标左右键没有按下时) 鼠标左键双击
            else if(p_key_data->vkCode=='A'/*gba a*/){
                mouse_logger.println("MOUSE LEFT DOUBLE CLICK");
                Mouse::mouseLeftDoubleClick();
            }
            // <leader x>按下时(鼠标左右键没有按下时) 鼠标右键单击
            else if(p_key_data->vkCode=='X'/*gba x*/){
                mouse_logger.println("MOUSE RIGHT CLICK");
                Mouse::mouseRightClick();
            }
            // <leader s>按下时(鼠标左右键没有按下时) 鼠标左键按下
            else if(p_key_data->vkCode=='S'/*select*/){
                mouse_logger.println("MOUSE LEFT DOWN");
                Mouse::mouseLeftDown();
                is_mouse_left_down=true;
            }
            // <leader i>按下时(鼠标左右键没有按下时) 鼠标右键按下
            else if(p_key_data->vkCode=='I'/*invert select*/){
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
            if(p_key_data->vkCode==leader_keycode){
                is_leader_down=false;
            }
        }
    }
    return CallNextHookEx(NULL, n_code, w_param, l_param);
}
