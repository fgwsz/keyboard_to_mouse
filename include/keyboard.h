#pragma once
#include<string>
#include<Windows.h>
#include<unordered_map>

class KeyBoard{
public:
    // 将输入的键盘按键值转化为按键名称
    static ::std::string const& keyCodeToName(DWORD key_code);
private:
    static ::std::unordered_map<DWORD,::std::string> _key_code_to_name_map;
    static void _emplace(DWORD key_code,::std::string const& key_name);
    static bool _init();
    static bool _init_flag;
};
::std::unordered_map<DWORD,::std::string> KeyBoard::_key_code_to_name_map{};
bool KeyBoard::_init_flag=false;

void KeyBoard::_emplace(DWORD key_code,::std::string const& key_name){
    _key_code_to_name_map.emplace(key_code,key_name);
};
bool KeyBoard::_init(){
    for(DWORD key_code='A';key_code<='Z';++key_code){
        KeyBoard::_emplace(key_code,::std::string(1,key_code));
    }
    for(DWORD key_code='0';key_code<='9';++key_code){
        KeyBoard::_emplace(key_code,::std::string(1,key_code));
    }
    KeyBoard::_emplace(160,"LeftShift"  );
    KeyBoard::_emplace(161,"RightShfit" );
    KeyBoard::_emplace(162,"LeftCtrl"   );
    KeyBoard::_emplace(163,"RightCtrl"  );
    KeyBoard::_emplace(164,"LeftAlt"    );
    KeyBoard::_emplace(165,"RightAlt"   );
    KeyBoard::_emplace(27 ,"Esc"        );
    KeyBoard::_emplace(9  ,"Tab"        );
    KeyBoard::_emplace(8  ,"Backspace"  );
    KeyBoard::_emplace(13 ,"Enter"      );
    KeyBoard::_emplace(20 ,"CapsLk"     );
    KeyBoard::_emplace(93 ,"Application");
    KeyBoard::_emplace(32 ,"Space"      );
    KeyBoard::_emplace(38 ,"Up"         );
    KeyBoard::_emplace(40 ,"Down"       );
    KeyBoard::_emplace(37 ,"Left"       );
    KeyBoard::_emplace(39 ,"Right"      );
    KeyBoard::_emplace(91 ,"Win"        );
    KeyBoard::_emplace(112,"F1"         );
    KeyBoard::_emplace(113,"F2"         );
    KeyBoard::_emplace(114,"F3"         );
    KeyBoard::_emplace(115,"F4"         );
    KeyBoard::_emplace(116,"F5"         );
    KeyBoard::_emplace(117,"F6"         );
    KeyBoard::_emplace(118,"F7"         );
    KeyBoard::_emplace(119,"F8"         );
    KeyBoard::_emplace(120,"F9"         );
    KeyBoard::_emplace(121,"F10"        );
    KeyBoard::_emplace(122,"F11"        );
    KeyBoard::_emplace(123,"F12"        );
    KeyBoard::_emplace(189,"-"          );
    KeyBoard::_emplace(187,"="          );
    KeyBoard::_emplace(219,"["          );
    KeyBoard::_emplace(221,"]"          );
    KeyBoard::_emplace(220,"|"          );
    KeyBoard::_emplace(186,";"          );
    KeyBoard::_emplace(222,"\'"         );
    KeyBoard::_emplace(188,","          );
    KeyBoard::_emplace(190,"."          );
    KeyBoard::_emplace(191,"/"          );
    return true;
}
::std::string const& KeyBoard::keyCodeToName(DWORD key_code){
    if(!KeyBoard::_init_flag){
        KeyBoard::_init();
        KeyBoard::_init_flag=true;
    }
    if(KeyBoard::_key_code_to_name_map.count(key_code)==0){
        KeyBoard::_emplace(key_code,::std::to_string(key_code));
    }
    return KeyBoard::_key_code_to_name_map.at(key_code);
}
