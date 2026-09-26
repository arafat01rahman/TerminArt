#!/bin/bash
# Script to generate HTML files for the 4 examples

set -e

# Create output directory
mkdir -p output

# Generate HTML for each example
./termart examples/dp.jpg --html --output output/dp.html
./termart examples/im.jpg --html --output output/im.html
./termart examples/lok.jpg --html --output output/lok.html
./termart examples/messi3.jpg --html --output output/messi3.html

# List generated files
echo "Generated HTML files in output/:"
ls -la output/