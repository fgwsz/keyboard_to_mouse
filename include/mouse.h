#pragma once
#include<Windows.h>

class Mouse{
public:
    // 模拟鼠标左键按下
    static void mouseLeftDown();
    // 模拟鼠标左键抬起
    static void mouseLeftUp();
    // 模拟鼠标右键按下
    static void mouseRightDown();
    // 模拟鼠标右键抬起
    static void mouseRightUp();
    // 模拟鼠标左键单击
    static void mouseLeftClick();
    // 模拟鼠标左键双击
    static void mouseLeftDoubleClick();
    // 模拟鼠标右键单击
    static void mouseRightClick();
    // 模拟鼠标向上移动
    static void mouseMoveUp();
    // 模拟鼠标向下移动
    static void mouseMoveDown();
    // 模拟鼠标向左移动
    static void mouseMoveLeft();
    // 模拟鼠标向右移动
    static void mouseMoveRight();
    // 模拟鼠标滚轮向上滑动
    static void mouseWheelUp();
    // 模拟鼠标滚轮向下滑动
    static void mouseWheelDown();
    // 鼠标位置结构体
    struct Position{
        // x坐标
        int x;
        // y坐标
        int y;
    };
    // 得到鼠标所在位置
    static void mousePosition(Position& position);
private:
    static void _mouseClick(DWORD dw_flags);
    static void _mouseMove(LONG dx,LONG dy);
    static void _mouseWheel(DWORD scroll_amount);
public:
    static DWORD current_dpixel_;
    static constexpr DWORD default_dpixel_=16;
};

DWORD Mouse::current_dpixel_=Mouse::default_dpixel_;

void Mouse::_mouseClick(DWORD dw_flags){
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
void Mouse::_mouseMove(LONG dx,LONG dy){
    POINT cursor_pos;
    GetCursorPos(&cursor_pos);
    SetCursorPos(cursor_pos.x+dx, cursor_pos.y+dy);
}
void Mouse::_mouseWheel(DWORD scroll_amount){
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    input.mi.mouseData = scroll_amount;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;
    SendInput(1, &input, sizeof(INPUT));
}
void Mouse::mouseLeftDown(){
    Mouse::_mouseClick(MOUSEEVENTF_LEFTDOWN);
}
void Mouse::mouseLeftUp(){
    Mouse::_mouseClick(MOUSEEVENTF_LEFTUP);
}
void Mouse::mouseRightDown(){
    Mouse::_mouseClick(MOUSEEVENTF_RIGHTDOWN);
}
void Mouse::mouseRightUp(){
    Mouse::_mouseClick(MOUSEEVENTF_RIGHTUP);
}
void Mouse::mouseLeftClick() {
    Mouse::_mouseClick(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP);
}
void Mouse:: mouseLeftDoubleClick() {
    Mouse::mouseLeftClick();
    Mouse::mouseLeftClick();
}
void Mouse:: mouseRightClick() {
    Mouse::_mouseClick(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP);
}
void Mouse:: mouseMoveUp(){
    Mouse::_mouseMove(0,-static_cast<LONG>(Mouse::current_dpixel_));
}
void Mouse:: mouseMoveDown(){
    Mouse::_mouseMove(0,static_cast<LONG>(Mouse::current_dpixel_));
}
void Mouse:: mouseMoveLeft(){
    Mouse::_mouseMove(-static_cast<LONG>(Mouse::current_dpixel_),0);
}
void Mouse:: mouseMoveRight(){
    Mouse::_mouseMove(static_cast<LONG>(Mouse::current_dpixel_),0);
}
void Mouse:: mouseWheelUp(){
    Mouse::_mouseWheel(static_cast<LONG>(Mouse::current_dpixel_));
}
void Mouse:: mouseWheelDown(){
    Mouse::_mouseWheel(-static_cast<LONG>(Mouse::current_dpixel_));
}
void Mouse::mousePosition(Mouse::Position& position){
    POINT point;
    GetCursorPos(&point);
    position.x=point.x;
    position.y=point.y;
}
