git add include/*
git add src/*
git add CMakeLists.txt
git add keyboard_to_mouse.exe
git add README.md
git add msvc_build.ps1
git add mingw_build.ps1
git add git_push.ps1
$commit_info=Read-Host -Prompt "input commit info"
git commit -m $commit_info
git push
