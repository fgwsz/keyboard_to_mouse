#pragma once
#include<string>
#include<Windows.h>
#include<unordered_map>

class KeyBoard{
public:
    // 将输入的键盘按键值转化为按键名称
    static ::std::string const& keyCodeToName(DWORD key_code);
private:
    static ::std::unordered_map<DWORD,::std::string> key_code_to_name_map_;
    static bool init_flag_;
    static bool _init();
};

::std::unordered_map<DWORD,::std::string> KeyBoard::key_code_to_name_map_{};

bool KeyBoard::init_flag_=KeyBoard::_init();

bool KeyBoard::_init(){
    for(DWORD key_code='A';key_code<='Z';++key_code){
        KeyBoard::key_code_to_name_map_.emplace(key_code,::std::string(1,key_code));
    }
    for(DWORD key_code='0';key_code<='9';++key_code){
        KeyBoard::key_code_to_name_map_.emplace(key_code,::std::string(1,key_code));
    }
    KeyBoard::key_code_to_name_map_.emplace(8  ,"Backspace"  );
    KeyBoard::key_code_to_name_map_.emplace(9  ,"Tab"        );
    KeyBoard::key_code_to_name_map_.emplace(13 ,"Enter"      );

    KeyBoard::key_code_to_name_map_.emplace(19 ,"PauseBreak" );
    KeyBoard::key_code_to_name_map_.emplace(20 ,"CapsLk"     );

    KeyBoard::key_code_to_name_map_.emplace(27 ,"Esc"        );

    KeyBoard::key_code_to_name_map_.emplace(32 ,"Space"      );
    KeyBoard::key_code_to_name_map_.emplace(33 ,"PageUp"     );
    KeyBoard::key_code_to_name_map_.emplace(34 ,"PageDown"   );
    KeyBoard::key_code_to_name_map_.emplace(35 ,"End"        );
    KeyBoard::key_code_to_name_map_.emplace(36 ,"Home"       );
    KeyBoard::key_code_to_name_map_.emplace(37 ,"Left"       );
    KeyBoard::key_code_to_name_map_.emplace(38 ,"Up"         );
    KeyBoard::key_code_to_name_map_.emplace(39 ,"Right"      );
    KeyBoard::key_code_to_name_map_.emplace(40 ,"Down"       );

    KeyBoard::key_code_to_name_map_.emplace(44 ,"PrintScreen");
    KeyBoard::key_code_to_name_map_.emplace(45 ,"Insert"     );
    KeyBoard::key_code_to_name_map_.emplace(46 ,"Delete"     );

    KeyBoard::key_code_to_name_map_.emplace(91 ,"LeftWin"    );
    KeyBoard::key_code_to_name_map_.emplace(92 ,"RightWin"   );
    KeyBoard::key_code_to_name_map_.emplace(93 ,"Application");

    KeyBoard::key_code_to_name_map_.emplace(106,"*"         );
    KeyBoard::key_code_to_name_map_.emplace(107,"+"         );

    KeyBoard::key_code_to_name_map_.emplace(109,"-"         );

    KeyBoard::key_code_to_name_map_.emplace(111,"/"         );
    KeyBoard::key_code_to_name_map_.emplace(112,"F1"         );
    KeyBoard::key_code_to_name_map_.emplace(113,"F2"         );
    KeyBoard::key_code_to_name_map_.emplace(114,"F3"         );
    KeyBoard::key_code_to_name_map_.emplace(115,"F4"         );
    KeyBoard::key_code_to_name_map_.emplace(116,"F5"         );
    KeyBoard::key_code_to_name_map_.emplace(117,"F6"         );
    KeyBoard::key_code_to_name_map_.emplace(118,"F7"         );
    KeyBoard::key_code_to_name_map_.emplace(119,"F8"         );
    KeyBoard::key_code_to_name_map_.emplace(120,"F9"         );
    KeyBoard::key_code_to_name_map_.emplace(121,"F10"        );
    KeyBoard::key_code_to_name_map_.emplace(122,"F11"        );
    KeyBoard::key_code_to_name_map_.emplace(123,"F12"        );

    KeyBoard::key_code_to_name_map_.emplace(144,"NumLock"    );
    KeyBoard::key_code_to_name_map_.emplace(145,"ScrollLock" );

    KeyBoard::key_code_to_name_map_.emplace(160,"LeftShift"  );
    KeyBoard::key_code_to_name_map_.emplace(161,"RightShfit" );
    KeyBoard::key_code_to_name_map_.emplace(162,"LeftCtrl"   );
    KeyBoard::key_code_to_name_map_.emplace(163,"RightCtrl"  );
    KeyBoard::key_code_to_name_map_.emplace(164,"LeftAlt"    );
    KeyBoard::key_code_to_name_map_.emplace(165,"RightAlt"   );

    KeyBoard::key_code_to_name_map_.emplace(186,";"          );
    KeyBoard::key_code_to_name_map_.emplace(187,"="          );
    KeyBoard::key_code_to_name_map_.emplace(188,","          );
    KeyBoard::key_code_to_name_map_.emplace(189,"-"          );
    KeyBoard::key_code_to_name_map_.emplace(190,"."          );
    KeyBoard::key_code_to_name_map_.emplace(191,"/"          );
    KeyBoard::key_code_to_name_map_.emplace(192,"`"          );

    KeyBoard::key_code_to_name_map_.emplace(219,"["          );
    KeyBoard::key_code_to_name_map_.emplace(220,"|"          );
    KeyBoard::key_code_to_name_map_.emplace(221,"]"          );
    KeyBoard::key_code_to_name_map_.emplace(222,"\'"         );
    return true;
}

::std::string const& KeyBoard::keyCodeToName(DWORD key_code){
    if(KeyBoard::key_code_to_name_map_.count(key_code)==0){
        KeyBoard::key_code_to_name_map_.emplace(key_code,::std::to_string(key_code));
    }
    return KeyBoard::key_code_to_name_map_.at(key_code);
}
