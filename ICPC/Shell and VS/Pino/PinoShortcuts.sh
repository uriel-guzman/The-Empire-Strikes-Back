############ This is just personal taste, just change to the properly directory ############

alias bash='gedit ~/.zshenv' # Bash file xd
alias icpc='cd /home/roberto/The-Empire-Strikes-Back' # Folder of github

drawingsDir='/home/roberto/programs/drawings/' # Folder where you store all the images and stuff

############################################################################################

#########shortcuts.txt#########
alias pull='git pull origin master'
red='\x1B[0;31m'
green='\x1B[0;32m'
blue='\x1B[0;34m'
noColor='\x1B[0m'


alias flags='-Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -fmax-errors=2 -O2'

push() {
  git add $1 && git commit -a -m "$2" && git push origin master
}


go() {
	g++-7 --std=c++17 $2 $3 ${flags} $1.cpp && ./a.out 
}

debug() {
	go $1 -DLOCAL "" < $2
	printf "\n"
} 

draw() {
	go $1 -DLOCAL -DDRAW < $2
	createBooks 
	printf "\n"
} 

run() {
	go $1 "" "" < $2	
	printf "\n"
}

test() {
	# test program input output
	g++-7 --std=c++17 $1.cpp -o prog 
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
	g++ --std=c++17 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -fmax-errors=3 -O2 -w $1.cpp -o prog
	g++ --std=c++17 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -fmax-errors=3 -O2 -w brute.cpp -o brute
	
	if [[ -f "gen.cpp" ]]; then
		 # C++ version, so first compile it
		g++-7 --std=c++17 gen.cpp -o gen 
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

############ This is just personal taste, just change to the properly directory ############

alias bash='gedit ~/.zshenv' # Bash file xd
alias icpc='cd /home/roberto/The-Empire-Strikes-Back' # Folder of github

drawingsDir='/home/roberto/programs/drawings/' # Folder where you store all the images and stuff

############################################################################################

red='\x1B[0;31m'
green='\x1B[0;32m'
blue='\x1B[0;34m'
noColor='\x1B[0m'

alias flags='-Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -fmax-errors=2 -O2'

go() {
	g++-7 --std=c++17 $2 $3 ${flags} $1.cpp && ./a.out 
}

debug() {
	go $1 -DLOCAL "" < $2
	printf "\n"
} 

draw() {
	go $1 -DLOCAL -DDRAW < $2
	createBooks 
	printf "\n"
} 

run() {
	go $1 "" "" < $2
	printf "awatafak"	
	printf "\n"
}

test() {
	# test program input output
	g++-7 --std=c++17 $1.cpp -o prog 
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
	g++-7 --std=c++17 $1.cpp -o prog 
	g++-7 --std=c++17 brute.cpp -o brute 
	
	if [[ -f "gen.cpp" ]]; then
		 # C++ version, so first compile it
		g++-7 --std=c++17 gen.cpp -o gen 
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

omegaup() {
	# Run it like:
	# omegaup program, without extension
	# at the gen.cpp file, use int main(int k)
	# k = 1, easy test cases
	# k = 2, medium test cases
	# k = 3, hard test cases

	compilation() {
		alias flags='-Wall -Wextra -Wshadow -fmax-errors=3 -w'
		g++-10 --std=c++17 $2 ${flags} $1.cpp -o $1.out 
	}

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
	echo "#Ejemplo\n || input\n || output\n  || description \n || end\n" >> "es.markdown"
	
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
  
	echo "- Para un 50 % de los casos (agrupados) los límites originales." >> "es.markdown"
	
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
		input="${casesDir}/medium.${i}.in"
		output="${casesDir}/medium.${i}.out"
		./gen.out medium > ${input}
		./$1.out < ${input} > ${output}	
	done
	
	# Big test cases
	for ((i = 1; i <= 15; i++)); do
		input="${casesDir}/big.${i}.in"
		output="${casesDir}/big.${i}.out"
		./gen.out is big > ${input}
		./$1.out < ${input} > ${output}	
	done

	
	clear
	printf "Ready to omegaup\n"
}


