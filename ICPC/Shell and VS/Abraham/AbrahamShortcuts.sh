alias myBash='open ~/.zshenv' # Bash file 

######################## Github ########################

alias icpc='cd /Users/abrahammurillo/The-Empire-Strikes-Back' # Folder of github
alias pull='git pull origin master && python3 /Users/abrahammurillo/The-Empire-Strikes-Back/ICPC/Shell\ and\ VS/Abraham/createSnippets.py'

push() {
	git add $1 && git commit -a -m "$2" && git push origin master
}

######################## Programming ########################

alias problems='cd /Users/abrahammurillo/Problems'

red='\x1B[0;31m'
green='\x1B[0;32m'
blue='\x1B[0;34m'
gray='\x1B[0;90m'
cyan='\x1B[0;36m'
noColor='\x1B[0m'

create() {
	tem='/Users/abrahammurillo/The-Empire-Strikes-Back/ICPC/Codes/Misc/template.cpp'

	begin=$1
	end=$1
	if [ $# -ge 2 ]; then
		# Then this is a contest, so input is needed
		end=$2 			
		tee {${begin}..${end}}.cpp < ${tem}
		touch {${begin}..${end}} 
	else
		# A single file
			
		tee ${begin}.cpp < ${tem}
		open ${begin}.cpp
		touch in
	fi
}

erase() {
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
	
	for ((i = 1; i <= 300; i++)); do
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


omegaup() {
	# Run it like:
	# omegaup program, without extension
	# at the gen.cpp file, use int main(int k)
	# k = 1, easy test cases
	# k = 2, medium test cases
	# k = 3, hard test cases

	myDir=$(pwd)

	compilation $1 "" 
	compilation gen "" 
	
	# Create folder
	problemName="problem_${1}"
	rm -r ${problemName}
	mkdir ${problemName}
	
	# Add solution and generator to the folder
	tee "${folderDir}/sol.cpp" < ${1}.cpp
	tee "${folderDir}/gen.cpp" < gen.cpp
	
	folderDir="${myDir}/${problemName}"
	cd ${folderDir}
	
	# Create cases and statements folder
	mkdir "cases"
	mkdir "statements"
	cd "${folderDir}/statements"
	touch "es.markdown"
	
	echo "# Descripción" >> "es.markdown"
	echo "Historia del problema" >> "es.markdown"
	echo "# Entrada\n Variables en \`rojo\`, solo \$texto\$\n" >> "es.markdown"
	echo "# Salida\n Como queremos la salida" >> "es.markdown"
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
	
	casesDir="${folderDir}/cases"

	cd ${myDir}	
	
	# Weak test cases
	for ((i = 1; i <= 3; i++)); do
		input="${casesDir}/${i}.in"
		output="${casesDir}/${i}.out"
		./gen.out > ${input}
		./$1.out < ${input} > ${output}	
	done
	
	# Medium test cases
	for ((i = 1; i <= 12; i++)); do
		input="${casesDir}/bunch1.medium.${i}.in"
		output="${casesDir}/bunch1.medium.${i}.out"
		./gen.out medium > ${input}
		./$1.out < ${input} > ${output}	
	done
	
	# Big test cases
	for ((i = 1; i <= 15; i++)); do
		input="${casesDir}/bunch2.hard.${i}.in"
		output="${casesDir}/bunch2.hard.${i}.out"
		./gen.out is big > ${input}
		./$1.out < ${input} > ${output}	
	done

	
	clear
	printf "Ready to omegaup\n"
}	