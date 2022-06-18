package com.example.appka3

class Post(
    var userId: Int = -1,
    var id:     Int = -1,
    var title:  String = "",
    var body:   String = ""
) {
    var comments: ArrayList<Comment> = ArrayList()
    override fun toString(): String {
        var str = title.uppercase() + "\n\n" +
                "$body\n"
        return str
    }
}