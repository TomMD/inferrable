public class Ackermann {
   public static int Ack(int m, int n) {
      if (m == 0) {
       return n+1;
      } else if (n == 0) {
            return Ack(m-1,1);
      } else {
          return Ack(m-1, Ack(m,n-1));
      }
   }

   public static int falseNegative() {
       String foo = null;
       int len = 0;
       if(Ack(2,1) < 0) {
           return 1;
       }
       len = foo.length();
       return len;
   }

   public static void main(String[] args) {
       System.out.println(falseNegative());
   }
}
