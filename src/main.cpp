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

// 全局键盘钩子回调函数
static LRESULT CALLBACK _keyBoardCallBack(int n_code, WPARAM w_param, LPARAM l_param);

int main() {
    // 安装全局键盘钩子
    HHOOK h_hook = SetWindowsHookEx(WH_KEYBOARD_LL, _keyBoardCallBack, NULL, 0);
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

static LRESULT CALLBACK _keyBoardCallBack(int n_code, WPARAM w_param, LPARAM l_param) {
    static constexpr DWORD leader_keycode=164;//left alt
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
    if (n_code == HC_ACTION) {
        KBDLLHOOKSTRUCT* p_key_data = (KBDLLHOOKSTRUCT*)l_param;
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
            // <leader h>按下时 鼠标左移
            else if(is_leader_down&&p_key_data->vkCode=='H'/*vim h*/){ 
                mouse_logger.println("MOUSE MOVE LEFT");
                println_mouse_position_before_move();
                Mouse::mouseMoveLeft();
                println_mouse_position_after_move();
            }
            // <leader j>按下时 鼠标下移
            else if(is_leader_down&&p_key_data->vkCode=='J'/*vim j*/){
                mouse_logger.println("MOUSE MOVE DOWN");
                println_mouse_position_before_move();
                Mouse::mouseMoveDown();
                Mouse::mousePosition(mouse_position);
                println_mouse_position_after_move();
            }
            // <leader k>按下时 鼠标上移
            else if(is_leader_down&&p_key_data->vkCode=='K'/*vim k*/){
                mouse_logger.println("MOUSE MOVE UP");
                println_mouse_position_before_move();
                Mouse::mouseMoveUp();
                println_mouse_position_after_move();
            }
            // <leader l>按下时 鼠标右移
            else if(is_leader_down&&p_key_data->vkCode=='L'/*vim l*/){
                mouse_logger.println("MOUSE MOVE RIGHT");
                println_mouse_position_before_move();
                Mouse::mouseMoveRight();
                println_mouse_position_after_move();
            }
            // <leader o>按下时(鼠标左右键没有按下时) 鼠标左键单击
            else if(
                is_leader_down&&p_key_data->vkCode=='O'/*gba o*/&&
                !is_mouse_left_down&&
                !is_mouse_right_down
            ){
                mouse_logger.println("MOUSE LEFT CLICK");
                Mouse::mouseLeftClick();
            }
            // <leader a>按下时(鼠标左右键没有按下时) 鼠标左键双击
            else if(
                is_leader_down&&p_key_data->vkCode=='A'/*gba a*/&&
                !is_mouse_left_down&&
                !is_mouse_right_down
            ){
                mouse_logger.println("MOUSE LEFT DOUBLE CLICK");
                Mouse::mouseLeftDoubleClick();
            }
            // <leader x>按下时(鼠标左右键没有按下时) 鼠标右键单击
            else if(
                is_leader_down&&p_key_data->vkCode=='X'/*gba x*/&&
                !is_mouse_left_down&&
                !is_mouse_right_down
            ){
                mouse_logger.println("MOUSE RIGHT CLICK");
                Mouse::mouseRightClick();
            }
            // <leader b>按下时 鼠标滚轮上滑
            else if(is_leader_down&&p_key_data->vkCode=='B'/*back*/){
                mouse_logger.println("MOUSE WHEEL UP");
                Mouse::mouseWheelUp();
            }
            // <leader n>按下时 鼠标滚轮下滑
            else if(is_leader_down&&p_key_data->vkCode=='N'/*next*/){
                mouse_logger.println("MOUSE WHEEL DOWN");
                Mouse::mouseWheelDown();
            }
            // <leader s>按下时(鼠标左右键没有按下时) 鼠标左键按下
            else if(
                is_leader_down&&p_key_data->vkCode=='S'/*select*/&&
                !is_mouse_left_down&&
                !is_mouse_right_down
            ){
                mouse_logger.println("MOUSE LEFT DOWN");
                Mouse::mouseLeftDown();
                is_mouse_left_down=true;
            }
            // <leader i>按下时(鼠标左右键没有按下时) 鼠标右键按下
            else if(
                is_leader_down&&p_key_data->vkCode=='I'/*invert select*/&&
                !is_mouse_left_down&&
                !is_mouse_right_down
            ){
                mouse_logger.println("MOUSE RIGHT DOWN");
                Mouse::mouseRightDown();
                is_mouse_right_down=true;
            }
            // <leader u>按下时(鼠标左右键按下时) 鼠标左/右键松开
            else if(
                is_leader_down&&p_key_data->vkCode=='U'/*un select*/&&
                (is_mouse_left_down||is_mouse_right_down)
            ){
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
            // <leader q>按下时 程序退出
            else if(
                is_leader_down&&p_key_data->vkCode=='Q'/*quit*/
            ){
                exe_logger.println("EXE QUIT");
                exit(0);
            }
            // <leader 2>按下时 鼠标移动/滚轮滑动距离翻倍
            else if(
                is_leader_down&&p_key_data->vkCode=='2'
            ){
                mouse_logger.println("MOUSE D_PIXEL * 2");
                mouse_logger.println("MOUSE D_PIXEL BEFORE IS ",Mouse::current_dpixel_);
                Mouse::current_dpixel_=Mouse::current_dpixel_*2;
                mouse_logger.println("MOUSE D_PIXEL AFTER  IS ",Mouse::current_dpixel_);
            }
            // <leader ->按下时 鼠标移动/滚轮滑动距离减半
            else if(
                is_leader_down&&p_key_data->vkCode==189/*key code of `-`*/
            ){
                mouse_logger.println("MOUSE D_PIXEL / 2");
                mouse_logger.println("MOUSE D_PIXEL BEFORE IS ",Mouse::current_dpixel_);
                Mouse::current_dpixel_=Mouse::current_dpixel_/2==0
                    ?1
                    :Mouse::current_dpixel_/2
                ;
                mouse_logger.println("MOUSE D_PIXEL AFTER  IS ",Mouse::current_dpixel_);
            }
        }
        // 检查松开的键盘
        if (w_param == WM_KEYUP || w_param == WM_SYSKEYUP) {
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
