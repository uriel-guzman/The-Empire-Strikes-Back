# First install clang-format (brew install clang-format)

myDir=$(pwd)

echo ${myDir}

# Files ending with .cpp, .c, .h
allFiles="$(find "${myDir}" | grep '/$')"


for file in ${allFiles}; do
  printf "%s\n" "${file}"
done

# for file in **/*.{c,cpp,h}; do
#   if [ -f "${file}" ]; then
#     printf '%s\n' "${file}"
#   #   # clang-format --verbose -i --style=file ${file}
#   fi
# done