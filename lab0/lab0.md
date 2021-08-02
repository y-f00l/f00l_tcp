# CS144

## lab 0

### webget

- 这里要求我们实现一个可以通过http协议来拉取网页内容的函数get_URL()，函数的第一个参数是域名，第二个是内容在网站上的路径
- 这里不难，根据材料给出的需要阅读的接口就能知道需要如何实现
  - 首先通过TCPSocket来创建一个Socket对象
  - 通过这个对象的connect方法来和对应域名建立TCP连接
  - 发送HTTP协议的报文，注意每行要以\r\n结束
  - 写一个while循环，结束条件是，对象的eof方法返回true就结束
  - 否则就不断的读取传来的ByteStream，拼合后输出到屏幕上。

### in memory reliable byte stream

- 材料里要求我们实现writer和reader，两方使用一个buffer来通信，writer向buffer中写，reader从buffer中读。
- 这里我联想到了管道，writer从pipe的一端写，reader从pipe的一端读。
- 代码不难，按照注释实现就好，但我踩到了几个测试用例的坑点
  - 最开始针对input_end，我直接设置了eof成员为true，然后测试用例通不过
  - 所以设立了两个成员，一个是end，一个是eof_f，然后在input_end里设置end为true，这样保证了input_ended的输出是正确的，但是有的测试用例仍然通不过
  - 观察log后总结了一下：writer在input_end时，如果buffer不为空，那么就说明没到eof，如果buffer为空，那么就说明已经到了，这时候才可以设置eof_f。
  - 针对read，我最开始以为关于byte_read()返回读取的字节数是在read方法里对其进行更改，后来发现是在pop之后才增加，同时结合了上面eof的问题，我在这里做了个判断，如果pop后buffer为空，那么就说明到eof了，设置eof_f为true。

### summary

- 热身lab，花了半天时间。
