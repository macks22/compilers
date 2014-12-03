class Main {
    s : String <- "abcd";
    x : Int;
    y : Int <- 10;
    main () : Int {
      x <- in_int();
      out_string("test");
      out_string(s);
      out_int(x*2+(y-4))
    };
}
