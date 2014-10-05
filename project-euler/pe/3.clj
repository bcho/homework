(defmacro dbg[x] `(let [x# ~x] (println "dbg:" '~x "=" x#) x#))

(defn prime? [n]
  (let [upper-limit (+ (Math/sqrt n) 1)]
    (loop [i 2]
      (if (>= i n)
        true
        (if (= (mod n i) 0)
          false
          (recur (inc i)))))))

(defn decomp [n]
  (filter
    (fn [x] (not (= x 0)))
    (for [x (range 2 (long (Math/sqrt n)))]
      (if (and (prime? x) (= 0 (mod n x)))
        (dbg x)
        0))))

(defn problem-3 [n]
  (last (decomp n)))

(println (problem-3 600851475143))
