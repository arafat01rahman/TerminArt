#!/bin/bash

# Check if opencv4 is available
if pkg-config --exists opencv4; then
    echo "opencv4 found: $(pkg-config --modversion opencv4)"
else
    echo "opencv4 not found via pkg-config - install libopencv-dev"
    exit 1
fi

# Build the termart binary
make clean
make

# Create output folder
mkdir -p /home/arafat01rahman/Project/TerminArt/output

# Run termart for each example
./termart /home/arafat01rahman/Project/TerminArt/examples/dp.jpg --html --output /home/arafat01rahman/Project/TerminArt/output/dp.html

./termart /home/arafat01rahman/Project/TerminArt/examples/im.jpg --html --output /home/arafat01rahman/Project/TerminArt/output/im.html

./termart /home/arafat01rahman/Project/TerminArt/examples/lok.jpg --html --output /home/arafat01rahman/Project/TerminArt/output/lok.html

./termart /home/arafat01rahman/Project/TerminArt/examples/messi3.jpg --html --output /home/arafat01rahman/Project/TerminArt/output/messi3.html

echo "All examples processed successfully!"
