package com.example.appka3

class Comment(
    var postId: Int = -1,
    var id:     Int = -1,
    var name:   String = "",
    var email:  String = "",
    var body:   String = ""
) {
    override fun toString(): String {
        return "$name - $email\n\n $body \n"
    }
}