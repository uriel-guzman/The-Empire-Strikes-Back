alias mysql=/usr/local/mysql/bin/mysql
alias myBash='gedit ~/.zshenv' # Bash file 

######################## Github ########################

alias icpc='cd /Users/abraham/The-Empire-Strikes-Back' # Folder of github
alias pull='git pull origin master && python3 /Users/abraham/The-Empire-Strikes-Back/ICPC/Shell\ and\ VS/Abraham/createSnippets.py'

push() {
	git add $1 && git commit -a -m "$2" && git push origin master
}

######################## Programming ########################

alias problems='cd /Users/abraham/Problems'
drawingsDir='/Users/abraham/Problems/drawings/'

red='\x1B[0;31m'
green='\x1B[0;32m'
blue='\x1B[0;34m'
gray='\x1B[0;90m'
cyan='\x1B[0;36m'
noColor='\x1B[0m'

create() {
	tem='/Users/abraham/The-Empire-Strikes-Back/ICPC/Codes/Misc/tem.cpp'

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

timer() {
	start=$(ruby -e 'puts (Time.now.to_f * 1000).to_i')
	$@
	end=$(ruby -e 'puts (Time.now.to_f * 1000).to_i')
	elapsed=$((end - start))
	printf "\n=====\nUsed: ${elapsed} ms\n"
}

compilation() {
	alias flags='-Wall -Wextra -Wshadow -fmax-errors=3 -w'
	g++-9 --std=c++17 $2 ${flags} $1.cpp -o $1.out 
}

debug() {
	compilation $1 -DLOCAL 
	timer ./$1.out < $2
	printf "\n"
} 

run() {
	compilation $1 ""  
	timer ./$1.out < $2
	printf "\n"
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
		
		diff -uwi <(./$1.out < in) <(./brute.out < in) > /dev/null
		
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

	g++-9 --std=c++17 $1.cpp -o prog
	g++-9 --std=c++17 gen.cpp -o gen 
	
	# Create folder
	problemName="problem_${1}"
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
	echo "#Ejemplo\n ||input\n ||output\n ||end\n" >> "es.markdown"
	
	casesDir="${folderDir}/cases"

	cd ${myDir}	
	
	# Weak test cases
	for ((i = 1; i <= 30; i++)); do
		input="${casesDir}/${i}.in"
		output="${casesDir}/${i}.out"
		./gen.out > ${input}
		./$1.out < ${input} > ${output}	
	done
	
	# Medium test cases
	for ((i = 1; i <= 30; i++)); do
		input="${casesDir}/medium.${i}.in"
		output="${casesDir}/medium.${i}.out"
		./gen.out medium > ${input}
		./$1.out < ${input} > ${output}	
	done
	
	# Big test cases
	for ((i = 1; i <= 40; i++)); do
		input="${casesDir}/big.${i}.in"
		output="${casesDir}/big.${i}.out"
		./gen.out is big > ${input}
		./$1.out < ${input} > ${output}	
	done

	
	clear
	printf "Ready to omegaup\n"
}	

createBooks() {
	prevDir=$(pwd) # Current directory, but will be the previous after all of this stuff D:
	
	cd ${drawingsDir}
	
	# Array with names of all possible books
	possibleBooks=("weightedGraph" "weightedDigraph" "digraph" "graph" "trie" "aho" "sam" "eertree" "segtree")
	
	openFile='open'
	
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
			echo '\\documentclass[landscape]{article}' >> ${bookTEX}
		else
			echo '\\documentclass{article}' >> ${bookTEX}
		fi
		echo '\\usepackage{graphicx, wrapfig, geometry}' >> ${bookTEX}
		echo '\\geometry{a4paper,left=1cm,right=1cm,top=1cm,bottom=1cm}' >> ${bookTEX}
		echo '\\begin{document}' >> ${bookTEX}
		
		# Insert all images
		cnt=0
		for ((i = 1; ; i++)); do
			image=${drawingsDir}${name}${i}.png
			file=${drawingsDir}${name}${i}.dot
			
			# To avoid stupid errors, just erase the .dot file and if the .dot file don't exist, then the image neither
			[[ -f ${file} ]] || break # There isn't file for this image, then you have already finished :D
			rm -r ${file}
			cnt=1
			
			echo '\\clearpage' >> ${bookTEX}
			echo '\\newpage' >> ${bookTEX}
			echo '\\begin{figure}' >> ${bookTEX}
			echo '\\centering' >> ${bookTEX}
			echo '\\includegraphics[scale=.5]{'${image}'}' >> ${bookTEX}
			echo '\\end{figure}' >> ${bookTEX}
		done	
		echo '\\end{document}' >> ${bookTEX}
		
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

	exit
}