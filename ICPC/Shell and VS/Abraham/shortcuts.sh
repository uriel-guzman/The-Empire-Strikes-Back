alias myBash="open ~/.zshenv"
alias saveMyBash="source ~/.zshenv" 

user="/Users/abraham"
icpcDir="${user}/**/ICPC"

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
  git add $1 
  git commit -a -m "$2"
  git push origin master
}

myPull() {
  git pull origin master
  snippets
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

omegaup() {
  # omegaup solution [testCaseGenerator]
  # Inside the gen.cpp file you should need to add main(int k)
  # k will be {{1:easy}, {2:medium}, {3:hard}}

  myDir=$(pwd)

  solution=$1
  testCaseGenerator="gen"

  if [ $# -ge 2 ]; then
    testCaseGenerator=$2
  fi

  compile ${solution} "" 
  compile ${testCaseGenerator} "" 

  # Create folder
  problemName="problem_${solution}"
  rm -r ${problemName}
  mkdir ${problemName}

  # Add solution and generator to the folder
  tee "${folderDir}/sol.cpp" < ${solution}.cpp
  tee "${folderDir}/gen.cpp" < ${testCaseGenerator}.cpp

  folderDir="${myDir}/${problemName}"
  cd ${folderDir}

  # Create cases and statements folder
  mkdir "cases"
  mkdir "statements"

  # Add description on es.markdown
  cd "${folderDir}/statements"
  touch "es.markdown"

  echo "# Descripción" >> "es.markdown"
  echo "Historia del problema" >> "es.markdown"
  echo "# Entrada\n Variables en \`rojo\`, solo \$texto\$\n" >> "es.markdown"
  echo "# Salida\n Esto es la salida" >> "es.markdown"
  echo "#Ejemplo\n || input\n || output\n || description \n || end\n" >> "es.markdown"

  echo "# Límites\n" >> "es.markdown"
  echo "- \$1 \leq n \leq 10^5$" >> "es.markdown"
  echo "\n----------\n" >> "es.markdown"

  echo "# Subtareas\n" >> "es.markdown"
  echo "Para un 10 % de los casos:\n" >> "es.markdown"
  echo "- \$1 \leq n \leq 10$" >> "es.markdown"
  echo "\n----------\n" >> "es.markdown"

  echo "Para un 40 % de los casos (agrupados):\n" >> "es.markdown"
  echo "- \$1 \leq n \leq 10$" >> "es.markdown"
  echo "\n----------\n" >> "es.markdown"

  echo "Para un 50 % de los casos (agrupados) los límites originales." >> "es.markdown"

  testCasesDir="${folderDir}/cases"

  cd ${myDir}	

  # Weak test cases
  for ((i = 1; i <= 3; i++)); do
    input="${testCasesDir}/${i}.in"
    output="${testCasesDir}/${i}.out"
    ./${testCaseGenerator}.out > ${input}
    ./${solution}.out < ${input} > ${output}	
  done

  # Medium test cases
  for ((i = 1; i <= 12; i++)); do
  input="${testCasesDir}/bunch1.medium.${i}.in"
  output="${testCasesDir}/bunch1.medium.${i}.out"
  ./${testCaseGenerator}.out medium > ${input}
  ./${solution}.out < ${input} > ${output}	
  done

  # Big test cases
  for ((i = 1; i <= 15; i++)); do
  input="${testCasesDir}/bunch2.hard.${i}.in"
  output="${testCasesDir}/bunch2.hard.${i}.out"
  ./${testCaseGenerator}.out is big > ${input}
  ./${solution}.out < ${input} > ${output}	
  done

  clear
  printf "Ready to omegaup\n"
}