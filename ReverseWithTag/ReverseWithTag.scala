object ReverseWithTag {
  private def tokenize(text: String): List[String] = {
    if (text isEmpty) List()
    else {
      val tagStart = text.indexOf('<')
      tagStart match {
        case -1 => List(text)
        case 0 => {
          val tagEnd = text.indexOf('>')
          text.take(tagEnd + 1) :: tokenize(text.drop(tagEnd + 1))
        }
        case _ => text.take(tagStart) :: tokenize(text.drop(tagStart))
      }
    }
  }

  def reverseTokens(tokens: List[String]): List[String] = {
    def isTag(token: String) = { token(0) == '<' }
    def isCloseTag(token: String) = { isTag(token) && token(1) == '/' }

    def tagName(tag: String) = {
      val inside =
        if (isCloseTag(tag)) tag.drop(2).dropRight(1)
        else tag.drop(1).dropRight(1)
      inside.split(' ').head
    }

    def findCloseTag(index: Int, name: String): Int = {
      if (tokens isEmpty) 0
      else if (isCloseTag(tokens(index)) && tagName(tokens(index)) == name) index
      else findCloseTag(index + 1, name)
    }

    if (tokens isEmpty) List()
    else if (isTag(tokens.head)) {
      val closeIndex = findCloseTag(1, tagName(tokens.head))
      val insideElement = tokens.slice(1, closeIndex)
      val afterElement = tokens.drop(closeIndex + 1)

      reverseTokens(afterElement) ::: tokens(0) ::
      reverseTokens(insideElement) ::: tokens(closeIndex) :: Nil
    } else {
      reverseTokens(tokens.tail) :::
      tokens.head.reverse :: Nil
    }
  }

  def reverseText(text: String) = {
    val tokens = tokenize(text)
    reverseTokens(tokens).mkString
  }

  def main(args: Array[String]) = {
    println(reverseText("Hello <b attr='some'>Bold <i>Italic</i> words</b> World"))
  }
}
