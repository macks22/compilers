class Main {
    y : Int ;
    x : Int <- 2 ;
    print_fn(a: Int) : Int {
       out_int(a * 2)
   };
    main () : Int {
      {y <- 9;
      x <- print_fn( 4*x+(y-4));
      out_int(x)
      }
    };
}
