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
#force_color_prompt=yes

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

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
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

# my custom aliases
alias repo='cd /home/uriel/The\ Empire\ Strikes\ Back/'
alias icpc='cd /home/uriel/ICPC/'
alias vimrc='nvim ~/.vimrc'
alias bashrc='nvim ~/.bashrc'
alias bashcom='source ~/.bashrc'
alias cucei='cd /home/uriel/CUCEI'


#########shortcuts.txt#########
alias pull='git pull origin master'

red='\x1B[0;31m'
green='\x1B[0;32m'
blue='\x1B[0;34m'
noColor='\x1B[0m'

push() {
  git add $1 && git commit -a -m "$2" && git push origin master
}

go() {
	g++ --std=c++17 $2 $3 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -fmax-errors=3 -O2 -w $1.cpp && ./a.out 
}

debug() {
	go $1 -DLOCAL "" < $2
} 

draw() {
	go $1 -DLOCAL -DDRAW < $2
	createBooks
}

run() {
	go $1 "" "" < $2
}

test() {
	# test program input output
	g++ --std=c++17 $1.cpp -o prog 
	input="$1_in"
	output="$1_out"
	if [ $# -ge 2 ]; then
		input=$2 
		if [ $# -ge 3 ]; then
			output=$3 
		fi
	fi
	
	for ((i = 1; ; i++)); do
		[[ -f ${input}$i ]] || break
		printf "Test case #$i"
		
		diff -uwi <(./prog < ${input}$i) ${output}$i > $1_diff
		
		if [[ ! $? -eq 0 ]]; then
			printf "${red} Wrong answer ${noColor}\n"
		else
			printf "${green} Accepted ${noColor}\n"
		fi
	done
	
	rm -r prog
}

random() { 
	# random a
	g++ --std=c++17 $1.cpp -o prog 
	g++ --std=c++17 brute.cpp -o brute 
	
	if [[ -f "gen.cpp" ]]; then
		 # C++ version, so first compile it
		g++ --std=c++17 gen.cpp -o gen 
	fi
	
	generateTestCase() {
		# looks for the .cpp generator first, then the .py generator
		if [[ -f "gen.cpp" ]]; then
			./gen > in
		else
			python3 gen.py | cat > in 
		fi
	}
	
	for ((i = 1; i <= 300; i++)); do
		printf "Test case #${i}"
		
		generateTestCase
		diff -uwi <(./prog < in) <(./brute < in) > $1_diff
		
		if [[ ! $? -eq 0 ]]; then
			printf "${red} Wrong answer ${noColor}\n"
			break
		else
			printf "${green} Accepted ${noColor}\n"
		fi
	done
	
	rm -r prog brute
}

createBooks() {
	prevDir=$(pwd) # Current directory, but will be the previous after all of this stuff D:
  drawingsDir='/home/uriel/ICPC/drawings/'; # Folder where you store all the images and stuff
	
	cd ${drawingsDir} # Write all stuff here!
	
	# Array with names of all possible books
	possibleBooks=("weightedGraph" "weightedDigraph" "digraph" "graph" "trie" "aho" "sam" "eertree" "segtree")
	
	# Way to open files according to the OS
	openFile='xdg-open'
	if [[ "$(uname)" == "Darwin" ]]; then
		openFile='open'
	fi
	
	for name in ${possibleBooks[@]}; do
		bookTEX=${drawingsDir}${name}.tex
		if [[ -f ${bookTEX} ]]; then 
			rm -r ${bookTEX} # Clear everything you know about this to avoid stupid mistakes D:
		fi
		bookPDF=${drawingsDir}${name}.pdf
		if [[ -f ${bookPDF} ]]; then 
			rm -r ${bookPDF} # Clear everything you know about this to avoid stupid mistakes D: x2
		fi
	done
	
	mergeImages() {
		name=$1 # Name of the book, dumb
	
		bookTEX=${drawingsDir}${name}.tex  # tex book file
		touch ${bookTEX} # Create the book file
		
		# Insert information to latex document to build the book
		if [[ ${name} == 'segtree' ]]; then
			# The segtree file have to be horizontal
			echo '\documentclass[landscape]{article}' >> ${bookTEX}
		else
			echo '\documentclass{article}' >> ${bookTEX}
		fi
		echo '\usepackage{graphicx, wrapfig, geometry}' >> ${bookTEX}
		echo '\geometry{a4paper,left=1cm,right=1cm,top=1cm,bottom=1cm}' >> ${bookTEX}
		echo '\begin{document}' >> ${bookTEX}
		
		# Insert all images
		cnt=0
		for ((i = 1; ; i++)); do
			image=${drawingsDir}${name}${i}.png
			file=${drawingsDir}${name}${i}.dot
			
			# To avoid stupid errors, just erase the .dot file and if the .dot file don't exist, then the image neither
			[[ -f ${file} ]] || break # There isn't file for this image, then you have already finished :D
			rm -r ${file}
			cnt=1
			
			echo '\clearpage' >> ${bookTEX}
			echo '\newpage' >> ${bookTEX}
			echo '\begin{figure}' >> ${bookTEX}
			echo '\centering' >> ${bookTEX}
			echo '\includegraphics[scale=.5]{'${image}'}' >> ${bookTEX}
			echo '\end{figure}' >> ${bookTEX}
		done	
		echo '\end{document}' >> ${bookTEX}
		
		# Create the pdf if cnt != 0
		if [[ ${cnt} != 0 ]] ; then
			pdflatex -pdf ${bookTEX}
		fi
	}
	
	for name in ${possibleBooks[@]}; do
		bookPDF=${drawingsDir}${name}.pdf
		mergeImages ${name}
		if [[ -f ${bookPDF} ]]; then
			# If the book exist, then open it
			${openFile} ${bookPDF}
		fi
	done
	
	cd ${prevDir} # Return to the previous directory
	
	printf "All books done\n"
}
############################################
