# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# If set, the pattern "**" used in a pathname expansion context will
# match all files and zero or more directories and subdirectories.
#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color|*-256color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
force_color_prompt=yes

green='\[\033[01;32m\]'
blue='\[\033[01;34m\]'
magenta='\[\033[01;35m\]'
white='\[\033[01;00m\]'
cyan='\[\033[01;36m\]'
yellow='\[\033[01;33m\]'

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48
	# (ISO/IEC-6429). (Lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

git_branch() {
  git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/( \1)/'
}

if [ "$color_prompt" = yes ]; then
  PS1="${debian_chroot:+($debian_chroot)}${green}\u${white}: ${blue}\w${magenta} \$(git_branch)${white} \n  ${white}↳${white} "
else
  PS1="${debian_chroot:+($debian_chroot)}\u:\w\$ \$(git_branch)\$ "
fi

unset color_prompt force_color_prompt


# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
  PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# colored GCC warnings and errors
#export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

# some more ls aliases
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'


#! /bin/bash   
set -m

# Add an "alert" alias for long running commands.  Use like so:
#   sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi

# personal configurations
export VISUAL=nvim;
export EDITOR=nvim;

# my custom aliases
alias vim='cd ~/.config/nvim'
alias repo='cd /home/uriel/The\ Empire\ Strikes\ Back/'
alias icpc='cd /home/uriel/ICPC/'
alias bashrc='nvim ~/.bashrc'
alias bashcom='source ~/.bashrc'
alias cucei='cd /home/uriel/CUCEI'
alias nvim="/usr/bin/neovim5.0"

#########shortcuts.txt#########
red='\x1B[0;31m'
green='\x1B[0;32m'
blue='\x1B[0;34m'
cyan='\x1B[0;36m'
noColor='\x1B[0m'

cfc() {
  icpc && mkdir $1 && cd $1 && nvim a.cpp
}

compilation() {
	alias flags='-Wall -Wextra -Wshadow -fmax-errors=3 -w'
	g++-10 --std=c++17 $2 ${flags} $1.cpp -o $1.out 
}

debug() {
	file=$1
	input=$1

	if [ $# -ge 2 ]; then
		input=$2
	fi
	
	compilation ${file} -DLOCAL 


	./${file}.out < ${input}
	rm -r ./${file}.out
} 

run() {
	file=$1
	input=$1

	if [ $# -ge 2 ]; then
		input=$2
	fi
	
	compilation ${file} ""


	./${file}.out < ${input}
	rm -r ./${file}.out
}

random() {
	# random file
	
	compilation $1 "" 
	compilation brute ""
	
	if [[ -f "gen.cpp" ]]; then
		 # C++ version, so first compile it
		compilation gen ""
	fi
	
	generateTestCase() {
		# looks for the .cpp generator first, then the .py generator
		if [[ -f "gen.cpp" ]]; then
			./gen.out > in
		else
			python3 gen.py | cat > in 
		fi
	}
	
	for ((i = 1; i <= 500; i++)); do
		generateTestCase
		
		printf "Test case #${i}"
		
		diff -uwi <(./$1.out < in) <(./brute.out < in) > diff$1
		
		if [[ $? -eq 0 ]]; then
			printf "${green} Accepted ${noColor}\n"
		else
			printf "${red} Wrong answer ${noColor}\n"
			break
		fi
	done
}
############################################

export PATH=$PATH:"/usr/bin"

export NVM_DIR="$HOME/.nvim"
[ -s "$NVM_DIR/nvim.sh" ] && \. "$NVM_DIR/nvim.sh"  # This loads nvim
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion
