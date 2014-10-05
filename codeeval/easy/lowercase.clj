; Sample code to read in test cases:
; Open the file passed as the first command line argument
(with-open [rdr (clojure.java.io/reader (first *command-line-args*))]
  ; Read each line ignoring empty ones
  (doseq [line (remove empty? (line-seq rdr))]
    (println (clojure.string/lower-case line))))
