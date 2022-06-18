package com.example.appka3

import android.R
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.BaseAdapter
import android.widget.TextView


class CustomUserListAdapter: BaseAdapter() {
    lateinit var listData: ArrayList<User>
    lateinit var layoutInflater: LayoutInflater
    override fun getCount(): Int {
        return listData.size
    }
    override fun getItem(position: Int): Any {
        return listData[position]
    }
    override fun getItemId(position: Int): Long {
        return position as Long
    }

    override fun getView(position: Int, convertView: View?, parent: ViewGroup?): View {
        TODO("Not yet implemented")
    }
}