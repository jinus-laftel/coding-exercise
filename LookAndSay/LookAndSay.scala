class LookAndSay(digit: Int) {
  private def say(seq: String) = {
    def countSay(count: Int, digit: Char, remain: String): String = {
      if (remain isEmpty) count.toString + digit
      else if (remain.head != digit) count.toString + digit + countSay(1, remain.head, remain.tail)
      else countSay(count + 1, digit, remain.tail)
    }

    if (seq isEmpty) ""
    else countSay(1, seq.head, seq.tail)
  }

  def apply(index: Int) : String = {
    if (index == 0) digit.toString
    else say(apply(index - 1))
  }
}

object Main {
  def main(args: Array[String]) = {
    val seq = new LookAndSay(1)
    println( List.tabulate(5)(seq.apply) )
  }
}
