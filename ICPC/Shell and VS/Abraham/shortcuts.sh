alias myBash="open ~/.zshenv"
alias saveMyBash="source ~/.zshenv" 

user="/Users/abraham"
icpcDir="${user}/The-Empire-Strikes-Back/ICPC"

alias icpc="cd ${icpcDir}" 
alias problems="cd ${user}/Problems"
alias snippets="python3 ${icpcDir}/Shell\ and\ VS/createSnippets.py"

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
  open $1.cpp
  open $1
}

create() {
  templateCode="${icpcDir}/Codes/Misc/Template.cpp"

  begin=$1
  end=$1
  if [ $# -ge 2 ]; then
    # It's a contest
    end=$2
    tee {${begin}..${end}}.cpp < ${templateCode}
    touch {${begin}..${end}} 
  else
    # A single file
    tee ${begin}.cpp < ${templateCode}
    open ${begin}.cpp
    touch in
  fi
}

erase() {
  # Erase anything in between [begin, end]
  begin=$1
  end=$1
  if [ $# -ge 2 ]; then
    end=$2 
    rm -r {${begin}..${end}}.cpp 
    rm -r {${begin}..${end}} 
  else
    rm -r ${begin}.cpp
    rm -r ${begin}
  fi
}

compile() {
  # Compiles 'file' with g++ and using 'moreFlags'
  file=$1
  moreFlags=""
  if [ $# -ge 2 ]; then
    moreFlags=$2
  fi

  alias flags='-Wall -Wextra -Wshadow -fmax-errors=3 -w -mcmodel=medium'
  g++-11 --std=c++17 ${moreFlags} ${flags} ${file}.cpp -o ${file}.out 
}

run() {
  # debug cppFile [input]
  cppFile=$1
  input=$1
  if [ $# -ge 2 ]; then
    input=$2
  fi

  compile ${cppFile}

  ./${cppFile}.out < ${input}
  rm -r ./${cppFile}.out
}

debug() {
  # debug cppFile [input]
  cppFile=$1
  input=$1
  if [ $# -ge 2 ]; then
    input=$2
  fi

  compile ${cppFile} -DLOCAL

  ./${cppFile}.out < ${input}
  rm -r ./${cppFile}.out
} 

random() {
  # random solution [bruteForceSolution] [testCaseGenerator]

  solution=$1
  bruteForceSolution="brute"
  testCaseGenerator="gen"
  if [ $# -ge 2 ]; then
    bruteForceSolution=$2
    if [ $# -ge 3 ]; then
      testCaseGenerator=$3
    fi
  fi

  compile ${solution} 
  compile ${bruteForceSolution}

  if [[ -f ${testCaseGenerator}.cpp ]]; then
    # C++ version, so first compile it
    compile ${testCaseGenerator}
  fi

  generateTestCase() {
    # cpp > py testCaseGenerator
    if [[ -f ${testCaseGenerator}.cpp ]]; then
      ./${testCaseGenerator}.out > in
    else
      python3 ${testCaseGenerator}.py | cat > in 
    fi
  }

  for ((i = 1; i <= 300; i++)); do
    generateTestCase

    printf "Test case #${i}"

    diff -uwi <(./${solution}.out < in) <(./${bruteForceSolution}.out < in) > diff${solution}

    if [[ $? -eq 0 ]]; then
      printf "${green} Accepted ${removeColor}\n"
    else
      printf "${red} Wrong answer ${removeColor}\n"
      break
    fi
  done
}