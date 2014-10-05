(defmacro dbg[x] `(let [x# ~x] (println "dbg:" '~x "=" x#) x#))

(defn prime? [n]
  (let [upper-limit (+ (Math/sqrt n) 1)]
    (loop [i 2]
      (if (>= i n)
        true
        (if (= (mod n i) 0)
          false
          (recur (inc i)))))))

(defn next-prime-since [n]
  (loop [cur (inc n)]
    (if (prime? cur)
      cur
      (recur (inc cur)))))

(defn prime-seq
  ([] (prime-seq 2))
  ([n] (cons n (lazy-seq (prime-seq (next-prime-since n))))))


(defn problem-7 [n]
  (last (take n (prime-seq))))

(println (problem-7 10001))
