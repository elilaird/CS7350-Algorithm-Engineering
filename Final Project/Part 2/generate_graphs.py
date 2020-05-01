import argparse
from pprint import pprint
from random import seed
from random import randint


def _skewed_graph(V, E):
    print('\nbuilding skewed graph...\n')

    G = [ [] for _ in range(V) ]
    edge_count = 0
    seed(1)

    skewed_dist = []
    for i in range(V):
        for _ in range(V-i):
            skewed_dist.append(i)

    while edge_count < E:
        v = randint(0,V-1)
        e = skewed_dist[randint(0, len(skewed_dist)-1)]
        del skewed_dist[e]

        print(skewed_dist)
        if e not in G[v] and e != v:
            G[v].append(e)
            G[e].append(v)
            edge_count+=1

    return G


def _uniform_graph(V, E):
    print('\nbuilding uniform graph...\n')

    G = [ [] for _ in range(V) ]
    edge_count = 0
    seed(1)

    while edge_count < E:
        v = randint(0,V-1)
        e = randint(0,V-1)

        if e not in G[v] and e != v:
            G[v].append(e)
            G[e].append(v)
            edge_count+=1

    return G


def _cycle_graph(V):
    print('\nbuilding cyclic graph...\n')

    G = []

    for v in range(V):
        if v == V-1:
            G.append(0)
        else:
            G.append(v+1)

    return G

def _complete_graph(V):
    print('\nbuilding complete graph...\n')

    G = []

    for v in range(V):
        G.append([e for e in range(V) if e != v])

    return G

def build_graph(V, E, Type, verbose=0):

    if Type == 'complete':
        graph = _complete_graph(V)
    elif Type == 'cycle':
        graph = _cycle_graph(V)
    elif Type == 'uniform':
        if E >= V:
            print('E must be less than V')
            exit(1)
        graph = _uniform_graph(V,E)
    elif Type == 'skewed':
        if E >= V:
            print('E must be less than V')
            exit(1)
        graph = _skewed_graph(V,E)
    else:
        print('Incompatible graph type')
        exit(1)

    if verbose: pprint(graph)
    return graph


def main():

    #build command line arg parser
    parser = argparse.ArgumentParser(description="Command Line Args")
    parser.add_argument('vertices', help='number of vertices')
    parser.add_argument('edges', help='number of edges')
    parser.add_argument('type', help='graph type')

    args = parser.parse_args()

    V = args.vertices
    E = args.edges
    Type = args.type

    print('V:', V)
    print('E:', E)
    print('Type:', Type)

    #build graph
    G = build_graph(int(V), int(E), Type.lower(), verbose=1)





if __name__=='__main__':
    main()
