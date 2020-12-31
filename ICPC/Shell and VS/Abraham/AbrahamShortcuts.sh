alias mysql=/usr/local/mysql/bin/mysql
alias myBash='open ~/.zshenv' # Bash file xd
alias sourceMyBash='source .zshenv' 

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
noColor='\x1B[0m'

createContest() {
	tem='/Users/abraham/The-Empire-Strikes-Back/ICPC/Codes/Misc/tem.cpp'
		
	begin=$1
	end=$2 	
	tee {${begin}..${end}}.cpp < ${tem}
 	touch {${begin}..${end}} 	
}

eraseContest() {
	begin=$1
	end=$2 
	rm -r {${begin}..${end}}.cpp 
	rm -r {${begin}..${end}} 
}

go() {
	alias flags='-Wall -Wextra -Wshadow -fmax-errors=2 -O2'
	g++-9 --std=c++17 $2 $3 ${flags} $1.cpp && ./a.out 
}

debug() {
	go $1 -DLOCAL "" < $2
	printf "\n"
} 

draw() {
	go $1 -DLOCAL -DDRAW < $2
	osascript -e "tell application \"Terminal\" to do script \"createBooks\""
	printf "\n"
} 

run() {
	go $1 "" "" < $2	
	printf "\n"
}

test() {
	# test program input output
	g++-9 --std=c++17 $1.cpp -o prog 
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
	g++-9 --std=c++17 $1.cpp -o prog 
	g++-9 --std=c++17 brute.cpp -o brute 
	
	if [[ -f "gen.cpp" ]]; then
		 # C++ version, so first compile it
		g++-9 --std=c++17 gen.cpp -o gen 
	fi
	
	generateTestCase() {
		# looks for the .cpp generator first, then the .py generator
		if [[ -f "gen.cpp" ]]; then
			./gen > in
		else
			python3 gen.py | cat > in 
		fi
	}
	
	for ((i = 1; i <= 150; i++)); do
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

