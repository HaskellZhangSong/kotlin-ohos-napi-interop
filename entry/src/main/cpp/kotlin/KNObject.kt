import kotlinx.cinterop.*;
class KNObject {
    fun foo(s : String) : String {
        return "world"
    }
}

fun get5(): Int {
    return 5
}

fun inc(a: Int): Int {
    return a + 1
}

fun add(a: Int, b: Int): Int {
    return a + b
}