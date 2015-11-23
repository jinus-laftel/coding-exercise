class LookAndSay(digit: Int) {
  private def count(digit: Char)(seq: String): Int = {
    if (seq isEmpty) 0
    else if (seq.head != digit) 0
    else count(digit)(seq.tail) + 1
  }

  private def remain(digit: Char)(seq: String): String = {
    if (seq isEmpty) ""
    else if (seq.head != digit) seq
    else remain(digit)(seq.tail)
  }

  private def say(seq: String): String = {
    if (seq isEmpty) ""
    else count(seq.head)(seq).toString + seq.head + say(remain(seq.head)(seq))
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
