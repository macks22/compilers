

class Main {
    x : Int <- 7;
    f (x: Int): Int {
	out_int(x);
        let x: Int, y: Int in {
	   x <- 8; y <- 1;
           out_int (x + y)
        }
        tel;
        out_int(x)
    };

    main () : Int {
      {
	out_int(x);
        let x: Int, y: Int in {
	   x <- 2; y <- 3;
           f(x);
           out_int (x + y)
        }
        tel;
        out_int(x)
      }
    };
}
