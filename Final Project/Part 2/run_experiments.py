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
    if r == 1:
        return round(((v*(v-1))/2)*r) - 1
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

for pair in vertex_edge_pairs:
    for method in ordering:
        for type in graph_options:
            subprocess.call([GENERATEGRAPHSEXE,str(pair[0]),str(pair[1]), type])
            subprocess.call([ORDERINGEXE, 'graph.txt', str(ordering[method]), type, '0'])
