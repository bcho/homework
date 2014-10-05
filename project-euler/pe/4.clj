(defmacro dbg[x] `(let [x# ~x] (println "dbg:" '~x "=" x#) x#))

(require '[clojure.string :as str])

(defn palindrome?
  ([] true)
  ([single] true)
  ([head & more] (and
                   (= head (last more))
                   (apply palindrome? (drop-last 1 more)))))

(defn num-palindrome? [n]
  (apply palindrome? (str/split (str n) #"")))

(defn make-num [a b] (* a b))

(defn problem-4 []
  (last (sort
        (for [a (range 999 100 -1) b (range 999 100 -1)
              :let [n (make-num a b)]
              :when (num-palindrome? n)]
          n))))

(println (problem-4))
