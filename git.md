# git 操作

### git init 

初始化仓库

### git add "文件名"

将文件添加到暂存区

### git commit -m "说明"

将暂存区的文件提交到仓库，并添加说明

### git status

查看提交状态

### git diff "文件名"

可以查看该文件修改了哪些内容

### git log 

显示日志，会显示每次提交的版本号

### git reset --hard HEAD^ 

回退到上一个版本

### git reset --hard HEAD^^

回退到上上个版本

### git reset --hard HEAD~100

回退到前100个版本

### git reset --hard 版本号

通过版本号精心回退

### git reflog 可以查看回退之前新增的版本号

## 相关概念

工作区：你电脑上所使用的目录

版本库：.git里面存放了stage(暂存区)，还有自动创建的第一个分支master,以及指向master的一个指针HEAD

撤销修改：

git checkout --file 可以丢弃工作区的修改

例如：命令git checkout --readme.txt 的意思是，把readme.txt文件在工作区做的修改全部撤销，有两种情况

1，修改后，还没有添加到暂存区，使用撤销后，就回到和版本库一模一样得到状态，

2，放入暂存区后又有修改，撤销修改后就回到添加暂存区的状态

## 删除文件：

rm file

可以在工作区的目录下直接删除文件

但是如果想从版本库文件彻底删除，需要再执行commit 命令

## 远程仓库

1,创建ssh key

ssh-keygen -t rsa -C "youremail@example.com"


