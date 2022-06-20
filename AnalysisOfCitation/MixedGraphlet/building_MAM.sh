#!/bin/bash

mkdir -p MAMs
cd ../..
src/Pipeline/pipeline -ma -igraph AnalysisOfCitation/HepTh.nwk -m Q204 -orb 1 -omam AnalysisOfCitation/MixedGraphlet/MAMs/HepTH_Q204_orb1.mam -nth 4
src/Pipeline/pipeline -ma -igraph AnalysisOfCitation/HepTh.nwk -m Q204 -orb 2 -omam AnalysisOfCitation/MixedGraphlet/MAMs/HepTH_Q204_orb2.mam -nth 4
src/Pipeline/pipeline -ma -igraph AnalysisOfCitation/HepTh.nwk -m Q206 -orb 1 2 -omam AnalysisOfCitation/MixedGraphlet/MAMs/HepTH_Q206_orb12.mam -nth 4
src/Pipeline/pipeline -ma -igraph AnalysisOfCitation/HepTh.nwk -m Q206 -orb 3 -omam AnalysisOfCitation/MixedGraphlet/MAMs/HepTH_Q206_orb3.mam -nth 4
src/Pipeline/pipeline -ma -igraph AnalysisOfCitation/HepTh.nwk -m Q2252 -orb 1 -omam AnalysisOfCitation/MixedGraphlet/MAMs/HepTH_Q2252_orb1.mam -nth 4
src/Pipeline/pipeline -ma -igraph AnalysisOfCitation/HepTh.nwk -m Q2252 -orb 2 3 -omam AnalysisOfCitation/MixedGraphlet/MAMs/HepTH_Q2252_orb23.mam -nth 4
src/Pipeline/pipeline -ma -igraph AnalysisOfCitation/HepTh.nwk -m Q2254 -orb 1 2 -omam AnalysisOfCitation/MixedGraphlet/MAMs/HepTH_Q2254_orb12.mam -nth 4
src/Pipeline/pipeline -ma -igraph AnalysisOfCitation/HepTh.nwk -m Q2254 -orb 3 4 -omam AnalysisOfCitation/MixedGraphlet/MAMs/HepTH_Q2254_orb34.mam -nth 4

cd AnalysisOfCitation/MixedGraphlet
python3 building_MAM.py
