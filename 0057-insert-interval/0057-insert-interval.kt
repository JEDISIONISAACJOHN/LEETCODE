class Solution {
    fun merge(intervals: Array<IntArray>): Array<IntArray> {
        intervals.sortBy { it[0] }
        // intervals.forEach { println("${it[0]} ${it[1]}") }
        var result = arrayOf<IntArray>()
        var start: Int = intervals[0][0]
        var end: Int = intervals[0][1]
        for (i in 0 until intervals.size - 1) {
            if (end >= intervals[i + 1][0]) {
                end = Math.max(end, intervals[i + 1][1])
            } else{
                result += intArrayOf(start, end)
                start = intervals[i + 1][0]
                end = intervals[i + 1][1]
            }
        }
        result += intArrayOf(start, end)
        return result
    }
    fun insert(intervals: Array<IntArray>, newInterval: IntArray): Array<IntArray> {
        return merge(intervals.plus(newInterval))
    }
}