(require '[clojure.math.numeric-tower :as math])

(defn lcm-seq
  ([a] a)
  ([a & more] (apply lcm-seq
                     (cons (math/lcm a (first more)) (rest more)))))

(defn problem-5 [num-seq]
  (apply lcm-seq num-seq))

(println (problem-5 (range 1 20)))
