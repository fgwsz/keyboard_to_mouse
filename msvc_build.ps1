if(Test-Path -Path msvc_build){}else{
    mkdir msvc_build
}
cd msvc_build
cmake -G"Visual Studio 17 2022" ..
cmake --build .   
cd ..
cp msvc_build/Debug/keyboard_to_mouse.exe keyboard_to_mouse.exe
./keyboard_to_mouse.exe
