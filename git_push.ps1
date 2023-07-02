git add include/*
git add src/*
git add CMakeLists.txt
git add *.ps1
git add *.exe
git add README.md
echo "input commit info:"
$commit_info=Read-Host
git commit -m $commit_info
git push
