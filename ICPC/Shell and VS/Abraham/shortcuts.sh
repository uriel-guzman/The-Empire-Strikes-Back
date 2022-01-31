user="/Users/abraham"
icpcDir="${user}/The-Empire-Strikes-Back/ICPC"

alias myBash="open ~/.zshenv"
alias saveMyBash="source ~/.zshenv" 

alias icpc="cd ${icpcDir}" 
alias problems="cd ${user}/Problems"
alias snippets="python3 ${icpcDir}/Shell\ and\ VS/Abraham/update.py"
alias omegaup="python3 ${icpcDir}/Shell\ and\ VS/omegaup.py"

templateCode="${icpcDir}/Codes/Misc/Template.cpp"

red='\x1B[0;31m'
green='\x1B[0;32m'
blue='\x1B[0;34m'
gray='\x1B[0;90m'
cyan='\x1B[0;36m'
removeColor='\x1B[0m'

myPush() {
  git commit -m "$1"
  git push origin master
}

myPull() {
  git pull origin master
  snippets
}

solve() {
  file=$1
  filename="${file%.*}"
  open ${filename}.cpp
  open ${filename}
}

create() {
  if [ $# -ge 2 ]; then
    # It's a contest
    begin=$1
    end=$2
    tee {${begin}..${end}}.cpp < ${templateCode}
    touch {${begin}..${end}} 
  else
    # A single file
    tee $1.cpp < ${templateCode}
    open $1.cpp
    touch in
  fi
}

erase() {
  if [ $# -ge 2 ]; then
    # Erase anything in between [begin, end]
    begin=$1
    end=$2 
    rm {${begin}..${end}}.cpp
    rm {${begin}..${end}}
  else
    # Erase all with prefix $1 and any extension
    pref="${1%.*}"
    rm ${pref}.*
    rm -r ${pref}
  fi
}

compile() {
  # Compiles 'filename' with g++ and using 'moreFlags'
  filename=$1
  moreFlags=""
  if [ $# -ge 2 ]; then
    moreFlags=$2
  fi

  # alias flags='-Wall -Wextra -w -mcmodel=large'
  alias flags=''
  g++-11 --std=c++17 ${moreFlags} ${flags} ${filename}.cpp -o ${filename}.out 
}

go() {
  flags=$1
  file=$2
  input=$3

  filename="${file%.*}"

  compile ${filename} ${flags}
  
  ./${filename}.out < ${input}

  rm ${filename}.out
}

run() {
  go "" $1 $2
}

debug() {
  go -DLOCAL $1 $2
} 

random() {
  # random solution [brute] [generator]

  solution=$1
  brute="brute"
  generator="gen"
  if [ $# -ge 2 ]; then
    brute=$2
    if [ $# -ge 3 ]; then
      generator=$3
    fi
  fi

  compile ${solution} 
  compile ${brute}

  if [[ -f ${generator}.cpp ]]; then
    # C++ version, so first compile it
    compile ${generator}
  fi

  generateTestCase() {
    # cpp > py generator
    if [[ -f ${generator}.cpp ]]; then
      ./${generator}.out > in
    else
      python3 ${generator}.py | cat > in 
    fi
  }

  for ((i = 1; i <= 300; i++)); do
    printf "Test case #${i}"

    generateTestCase

    ./${solution}.out < in > myOut
    ./${brute}.out < in > bruteForceOut

    diff -ywi myOut bruteForceOut > diff${solution}

    if [[ $? -eq 0 ]]; then
      printf "${green} Accepted ${removeColor}\n"
    else
      printf "${red} Wrong answer ${removeColor}\n"
      open diff${solution}
      break
    fi
  done
}