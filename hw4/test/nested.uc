class Main {
    y : Int <- 0;
    x : Int <- 0;
    i : Int <- 0;

    main () : Int {
      while y < 50 loop {
        while x < 5 loop {
          y <- y + x;
          x <- if (x = x) then (if (x = x) then (x + 1) else x fi) else x fi
        } pool;
        i <- i + 1;
        x <- 0;
        out_int(y)
      } pool
    };
}
