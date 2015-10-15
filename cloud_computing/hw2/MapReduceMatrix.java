import java.io.BufferedReader;
import java.io.FileReader;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.TimeUnit;


/**
 * Base context 类.
 */
class BaseContext {

    protected HashMap<String, String> conf;
    
    public BaseContext(HashMap<String, String> conf) {
        this.conf = conf;
    }

    public String getConfigurationValue(String key) {
        if (this.conf.containsKey(key)) {
            return this.conf.get(key);
        }
        return "";
    }
}


/**
 * Map reduce 的 map context 类.
 */
class MapContext extends BaseContext {

    /**
     * 读取的文件输入
     */
    private final ConcurrentLinkedQueue<String> lines;

    /**
     * mapper 分组后的数据
     */
    public final ConcurrentHashMap<String, ConcurrentLinkedQueue<String>> values;

    public MapContext(HashMap<String, String> conf, BufferedReader in) {
        super(conf);

        lines = new ConcurrentLinkedQueue<String>();
        values = new ConcurrentHashMap<String, ConcurrentLinkedQueue<String>>();
        
        prepareInput(in);
        prepareValues();
    }

    public boolean nextKeyValue() {
        return !lines.isEmpty();
    }

    public String getCurrentKey() {
        return "";
    }

    public String getCurrentValue() {
        return lines.poll();
    }

    public void write(String outputKey, String outputValue) {
        values.get(outputKey).add(outputValue);
    }

    private void prepareInput(BufferedReader in) {
        // FIXME 太大的文件不支持
        try {
            String line;
            while (true) {
                line = in.readLine();
                if (line == null) {
                    break;
                }
                lines.add(line);
            }
        } catch (Exception e) {
            
        }
    }

    private void prepareValues() {
        int m = Integer.parseInt(getConfigurationValue("m"));
        int p = Integer.parseInt(getConfigurationValue("p"));

        String coordinate;
        for (int i = 0; i < m; i = i + 1) {
            for (int j = 0; j < p; j = j + 1) {
                coordinate = "" + i + "," + j;
                values.put(coordinate, new ConcurrentLinkedQueue<String>());
            }
        }
    }

}

/**
 * Map reduce 的 reduce context 类.
 */
class ReduceContext extends BaseContext {

    /**
     * mapper 分组后的数据
     */
    private final ConcurrentHashMap<String, ConcurrentLinkedQueue<String>> values;

    /**
     * mapper 分组后的组 keys
     */
    private final ConcurrentLinkedQueue<String> keys;

    public ReduceContext(HashMap<String, String> conf,
            ConcurrentHashMap<String, ConcurrentLinkedQueue<String>> values) {
        super(conf);

        this.values = values;
        this.keys = new ConcurrentLinkedQueue<String>();

        prepareValues();
    }

    public boolean nextKey() {
        return !this.keys.isEmpty();
    }

    public String getCurrentKey() {
        return this.keys.poll();
    }

    public Iterable<String> getValues(String key) {
        return values.get(key);
    }

    public void write(String outputKey, double outputValue) {
        System.out.println(outputKey + " " + outputValue);
    }

    private void prepareValues() {
        for (Enumeration<String> e = values.keys(); e.hasMoreElements();) {
            keys.add(e.nextElement());
        }
    }
}

/**
 * Map reduce 的 mapper 类.
 */
class Mapper implements Runnable {

    private final MapContext context;

    public Mapper(MapContext context) {
        this.context = context;
    }

    protected void map(String key, String value, MapContext context) {
        // 每行输入形式： A,i,j,A[i, j] / B,i,j,B[i, j]
        String[] unit = value.split(",");

        int m = Integer.parseInt(context.getConfigurationValue("m"));
        int p = Integer.parseInt(context.getConfigurationValue("p"));
        
        // map 输出
        String outputKey;
        String outputValue;

        if (unit[0].equals("A")) {
            for (int k = 0; k < p; k = k + 1) {
                // 使用 A 矩阵的 <i, k> 作为键
                outputKey = unit[1] + "," + k;
                // 使用 A 矩阵的 <j, A[i, j]> 作为值
                outputValue = unit[0] + "," + unit[2] + "," + unit[3];

                // emit
                context.write(outputKey, outputValue);
            }
        } else {
            for (int k = 0; k < m; k = k + 1) {
                // 使用 B 矩阵的 <k, j> 作为键
                outputKey = k + "," + unit[2];
                // 使用 B 矩阵的 <i, B[i, j]> 作为值
                outputValue = unit[0] + "," + unit[1] + "," + unit[3];

                // emit
                context.write(outputKey, outputValue);
            }
        }
    }

    public void run() {
        // 处理输入
        while (context.nextKeyValue()) {
            // XXX
            String value = context.getCurrentValue();
            if (value == null) {
                break;
            }
            map(context.getCurrentKey(), value, context);
        }
    }
}

/**
 * Map reduce 的 reduce 类.
 */
class Reducer implements Runnable {

    private final ReduceContext context;

    public Reducer(ReduceContext context) {
        this.context = context;
    }

    protected void reduce(String key, Iterable<String> values, ReduceContext context) {
        String[] value;

        // 记录 A / B 矩阵的值
        HashMap<Integer, Double> a = new HashMap<Integer, Double>();
        HashMap<Integer, Double> b = new HashMap<Integer, Double>();

        for (String val : values) {
            value = val.split(",");
            int k = Integer.parseInt(value[1]);
            double item = Double.parseDouble(value[2]);

            if (value[0].equals("A")) {
                a.put(k, item);
            } else {
                b.put(k, item);
            }
        }

        int n = Integer.parseInt(context.getConfigurationValue("n"));
        double rv = 0.0f;
        double a_ij;
        double b_jk;
        // 执行累加
        for (int j = 0; j < n; j = j + 1) {
            a_ij = a.containsKey(j) ? a.get(j) : 0.0f;
            b_jk = b.containsKey(j) ? b.get(j) : 0.0f;
            rv = rv + a_ij * b_jk;
        }

        // emit
        context.write(key, rv);
    }

    public void run() {
        String key;
        while (context.nextKey()) {
            key = context.getCurrentKey();
            // XXX
            if (key == null) {
                break;
            }
            reduce(key, context.getValues(key), context);
        }
    }
}

/**
 * Map reduce 的任务类.
 */
class Job {
    private final int mapperThreadCount = 3;
    private final int reducerThreadCount = 10;

    private final ExecutorService mapExecutor;
    private final ExecutorService reduceExecutor;
    
    private HashMap<String, String> conf;
    private final MapContext mapContext;
    private final int mapperCount;
    private final int reducerCount;

    public Job(HashMap<String, String> conf, MapContext mapContext, int mapperCount, int reducerCount) {
        mapExecutor = Executors.newFixedThreadPool(mapperThreadCount);
        reduceExecutor = Executors.newFixedThreadPool(reducerThreadCount);

        this.conf = conf;
        this.mapContext = mapContext;
        this.mapperCount = mapperCount;
        this.reducerCount = reducerCount;
    }

    public void start() {
        // map
        for (int i = 0; i < mapperCount; i = i + 1) {
            mapExecutor.execute(new Mapper(mapContext));
        }
        mapExecutor.shutdown();
        try {
            mapExecutor.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
        } catch (InterruptedException e) {
        }

        // reduce
        ReduceContext reduceContext = new ReduceContext(conf, mapContext.values);
        for (int i = 0; i < reducerCount; i = i + 1) {
            reduceExecutor.execute(new Reducer(reduceContext));
        }
        reduceExecutor.shutdown();
    }

    public void shutdown() {
        mapExecutor.shutdown();
        reduceExecutor.shutdown();
    }

}

public class MapReduceMatrix {
    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            Runtime.getRuntime().exit(1);
        }

        HashMap<String, String> conf = new HashMap<String, String>();
        BufferedReader in = new BufferedReader(new FileReader(args[0]));

        String size = in.readLine();
        String[] mnp = size.split(",");
        conf.put("n", mnp[1]);
        conf.put("m", mnp[0]);
        conf.put("p", mnp[2]);

        MapContext mapContext = new MapContext(conf, in);

        Job job = new Job(conf, mapContext, 100, 10);
        job.start();
        job.shutdown();
    }
}
