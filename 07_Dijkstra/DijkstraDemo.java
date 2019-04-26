/**

 * Dijkstra最短路径算法

 */

public static Map<Integer,Integer>dijkstra(Graph graph,int startIndex){

    //创建距离表，存储从起点到每一个顶点的临时距离
    Map<Integer,Integer>distanceMa=new HashMap<Integer,Integer>();
    //记录遍历过的顶点
    Set<Integer>accessedSe=new HashSet<Integer>();
    //图的顶点数量
    int siz=graph.vertexes.length;
    //初始化最短路径表，到达每个顶点的路径代价默认为无穷大
    for(int i=1;i<size;i++){
        distanceMap.put(i,Integer.MAX_VALUE);
    }
    //遍历起点，刷新距离表
    accessedSet.add(0);
    List<Edge>edgesFromStar=graph.adj[startIndex];
    for(Edge edg:edgesFromStart)
    {
        distanceMap.put(edge.index,edge.weight);
    }
    //主循环，重复 遍历最短距离顶点和刷新距离表 的操作
    for(int i=1;i<size;i++)
    {
        //寻找最短距离顶点
        int minDistanceFromStar=Integer.MAX_VALUE;
        int minDistanceInde=-1;
        for(int j=1;j<size;j++)
        {
            if(!accessedSet.contains(j)&&distanceMap.get(j)<minDistanceFromStart){
                minDistanceFromStar=distanceMap.get(j);
                minDistanceInde=j;
            }
        }
        if(minDistanceInde==-1){
            break;
        }
        //遍历顶点，刷新距离表
        accessedSet.add(minDistanceIndex);  
        for(Edge edg:graph.adj[minDistanceIndex])
        {
            if(accessedSet.contains(edge.index)){
                continue;
            }
            int weigh=edge.weight;
            int preDistanc=distanceMap.get(edge.index);
            if(weigh!=Integer.MAX_VALUE&&(minDistanceFromStart+weigh<preDistance))
            {
                distanceMap.put(edge.index,minDistanceFromStar+weight);
            }
        }
    }
    return distanceMap;
}
public static void main(String[]args){
    Graph grap=new Graph(7);
    initGraph(graph);
    Map<Integer,Integer>distanceMa=dijkstra(graph,0);
    int distanc=distanceMap.get(6);
    System.out.println(distance);
}
/**
 * 
 * 图的顶点
 * 
 */
private static class Vertex {
	String data;
	Vertex(String data) {
		this.dat = data;
	}
}
/**
 * 
 * 图的边
 * 
 */
private static class Edge {
	int index;
	int weight;
	Edge(int index, int weight) {
		this.inde = index;
		this.weigh = weight;
	}
}
/**
 * 
 * 图
 * 
 */
private static class Graph {
	private Vertex[] vertexes;
	private LinkedList<Edge> adj[];
	Graph(int size) {
		// 初始化顶点和邻接矩阵
		vertexe = new Vertex[size];
		ad = new LinkedList[size];
		for (int i = 0; i < adj.length; i++) {
			adj[i] = new LinkedList<Edge>();
		}
	}
}

private static void initGraph(Graph graph){
    graph.vertexes[0] = new Vertex("A");
    graph.vertexes[1] = new Vertex("B");
    graph.vertexes[2] = new Vertex("C");
    graph.vertexes[3] = new Vertex("D");
    graph.vertexes[4] = new Vertex("E");
    graph.vertexes[5] = new Vertex("F");
    graph.vertexes[6] = new Vertex("G");

    graph.adj[0].add(new Edge(1, 5));
    graph.adj[0].add(new Edge(2, 2));
    graph.adj[1].add(new Edge(0, 5));
    graph.adj[1].add(new Edge(3, 1));
    graph.adj[1].add(new Edge(4, 6));
    graph.adj[2].add(new Edge(0, 2));
    graph.adj[2].add(new Edge(3, 6));
    graph.adj[2].add(new Edge(5, 8));
    graph.adj[3].add(new Edge(1, 1));
    graph.adj[3].add(new Edge(2, 6));
    graph.adj[3].add(new Edge(4, 1));
    graph.adj[3].add(new Edge(5, 2));
    graph.adj[4].add(new Edge(1, 6));
    graph.adj[4].add(new Edge(3, 1));
    graph.adj[4].add(new Edge(6, 7));
    graph.adj[5].add(new Edge(2, 8));
    graph.adj[5].add(new Edge(3, 2));
    graph.adj[5].add(new Edge(6, 3));
    graph.adj[6].add(new Edge(4, 7));
    graph.adj[6].add(new Edge(5, 3));

}
