if CommandLine.arguments.count != 2 {
    print("Usage: hello name")
} else {
    let name = CommandLine.arguments[1]
    sayHello(name: name)
}

