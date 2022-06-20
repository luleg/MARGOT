#!/bin/bash

cd ../..
src/Pipeline/pipeline -pa -isym AnalysisOfCitation/MixedGraphlet/HepTh_lcc.mam -c 1.1 -opart AnalysisOfCitation/MixedGraphlet/HepTh_mam.p
src/Pipeline/pipeline -pa -igraph AnalysisOfCitation/MixedGraphlet/HepTh_lcc.nwk -c 1.1 -opart AnalysisOfCitation/MixedGraphlet/HepTh_nwk.p
