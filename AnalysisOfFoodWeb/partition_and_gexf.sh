#!/bin/bash

cd ..
src/Pipeline/pipeline -igraph AnalysisOfFoodWeb/Florida-bay.nwk -m T108 -omam AnalysisOfFoodWeb/Florida-bay_T108.mam -opart AnalysisOfFoodWeb/Florida-bay_T108.p
cd AnalysisOfFoodWeb
python3 creating_gexf.py
