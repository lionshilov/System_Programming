#!/usr/bin/bash

# Default
resize=50%
ext=jpg
format=jpg

usage()
{
  echo "  $(basename $0) -i dir -o dir [-r resize] [-e extension] [-f convert file image extensions]"
  echo
  echo "OPTIONS                                             "
  echo "  -i: Input file image in directory     [default: none]"
  echo "  -o: Output file image in directory        [default: none]"
  echo "  -r: Resize file image      [default: 50%]"
  echo "  -e: File input extension      [default: jpg]"
  echo "  -f: File output convert extension     [default: jpg]"
}
[[ "$1" = -h ]] && { usage; exit; }

[[ $(which convert) = "" ]] && \
  {
  echo "Error: ImageMagick not installed";
  exit 1;
  }

while getopts ":i:o:r:e:f:" opt; do
  case $opt in
    i) idir=${OPTARG%/}; ;;  # Remove slash in Terminal
    o) odir=${OPTARG%/}; ;;  # Remove slash in Terminal
    r) resize=$OPTARG;   ;;
    e) ext=$OPTARG;      ;;
    f) format=$OPTARG    ;;
    \?) echo "Error: invalid option: -$OPTARG";             exit 1 ;;
    :)  echo "Error: option -$OPTARG requires an argument"; exit 1 ;;
  esac
done

[[ -z "$idir" ]] && { echo "Error: Non correctly input directory. Read Instructions, please.";  exit 1; }
[[ -z "$odir" ]] && { echo "Error: Non correctly output directory. Read Instructions, please."; exit 1; }

[[ $(shopt -s nullglob; echo "$idir"/*.$ext) = "" ]] \
  && { echo "Error: No image files $ext in directory $idir or non correctly write extensions in optinons"; exit 1; }

for image in "$idir"/*.$ext; do
  echo -n "Resize and Convert Image. Wait ${image##*/}... "
  # ImageMagick call
  mogrify "$image"     \
    -resize $resize  \
    -format $format \
    "$odir"/$(basename "$image")
  echo Done
done
