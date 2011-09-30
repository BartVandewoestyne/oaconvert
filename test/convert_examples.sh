#!/bin/bash

# Some complete maps.
../src/oa2pm ../openair_examples/AirspaceBelgium2.txt > output/AirspaceBelgium2.mp
../src/oa2pm ../openair_examples/WEEK_BE_FRONT.txt > output/WEEK_BE_FRONT.mp
../src/oa2pm ../openair_examples/winpilot_example.txt > output/winpilot_example.mp

# Some simple stand-alone examples with only 1 or 2 airspaces for debugging.
../src/oa2pm ../openair_examples/two_arcs.txt > output/two_arcs.mp
../src/oa2pm ../openair_examples/negative_arc.txt > output/negative_arc.mp
../src/oa2pm ../openair_examples/only_circle.txt > output/only_circle.mp
../src/oa2pm ../openair_examples/liege_ctr.txt > output/liege_ctr.mp
