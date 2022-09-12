#!/usr/bin/zsh
if [ -d "/goinfre" ]
then 
    echo "Dump version"
    MYPATH="/goinfre/$USER/miniconda3"
else
    echo "VM version"
    MYPATH="/home/$USER/miniconda3"
fi

if [ -d $MYPATH ]
then
    echo "use : conda activate 42AI-$USER"
    exit
else
    echo "Conda not found"
fi

if [ -f "./Miniconda3-latest-Linux-x86_64.sh" ]
then
    echo "Miniconda3-latest-Linux-x86_64.sh found"
else
    echo "Miniconda3-latest-Linux-x86_64.sh not found"
    curl -LO "https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh"
fi

rm -rf $MYPATH
sh Miniconda3-latest-Linux-x86_64.sh -b -p $MYPATH

$MYPATH/bin/conda init zsh
$MYPATH/bin/conda config --set auto_activate_base false

source ~/.zshrc

conda create -y --name 42AI-$USER python=3.7 jupyter pandas pycodestyle

conda info --envs
conda activate 42AI-$USER
which python
python -V
python -c "print('Hello World!')"
