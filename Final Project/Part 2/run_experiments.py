import os,sys
import subprocess
import enum

ORDERINGEXE = './cmake-build-debug/Final_Project'
GENERATEGRAPHSEXE = './generate_graphs'

ordering = {
    'SmallestLastOrdering'                    : 1,
    'WelshPowellOrdering'                     : 2,
    'UniformRandomOrdering'                   : 3,
    'LargestLastOrdering'                     : 4,
    'LargestEccentricityOrdering'             : 5,
    'DistanceFromHighestDegreeVertexOrdering' : 6
}


def E_ratio(v,r):
    return round(((v*(v-1))/2)*r)


graph_options = [
    'complete',
    'cycle',
    'uniform',
    'skewed'
]

vertex_edge_pairs = [
    (10,E_ratio(10,1)),
    (10,E_ratio(10,.5)),
    (10,E_ratio(10,.33)),
    (50,E_ratio(50,1)),
    (50,E_ratio(50,.5)),
    (50,E_ratio(50,.33)),
    (100,E_ratio(100,1)),
    (100,E_ratio(100,.5)),
    (100,E_ratio(100,.33)),
]

subprocess.call([GENERATEGRAPHSEXE,str(vertex_edge_pairs[0][0]),str(vertex_edge_pairs[0][1]), 'complete'])
subprocess.call([ORDERINGEXE, 'graph.txt', str(ordering['SmallestLastOrdering'])])
