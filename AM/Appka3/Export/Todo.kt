package com.example.appka3

class Todo(
    var userId: Int = -1,
    var id: Int = -1,
    var title: String = "",
    var completed: Boolean = false
) {
    override fun toString(): String {
        var str = ""
        if (completed) {
            str += "☑ "
        } else {
            str += "☐ "
        }
        str += "$title"
        return str
    }
}