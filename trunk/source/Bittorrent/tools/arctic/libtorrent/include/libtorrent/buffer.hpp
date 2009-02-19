/*
Copyright (c) 2003 - 2005, Arvid Norberg, Daniel Wallin
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the distribution.
    * Neither the name of Rasterbar Software nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef LIBTORRENT_BUFFER_HPP
#define LIBTORRENT_BUFFER_HPP

#include <memory>

namespace libtorrent {

class buffer
{
public:
    struct interval
    {
       interval(char* begin, char* end)
          : begin(begin)
          , end(end)
        {}

        char* begin;
        char* end;
    };

    struct const_interval
    {
       const_interval(char const* begin, char const* end)
          : begin(begin)
          , end(end)
        {}

        char const* begin;
        char const* end;
    };

    typedef std::pair<const_interval, const_interval> interval_type;

    buffer(std::size_t n = 0);
    ~buffer();

	 interval allocate(std::size_t n);
    void insert(char const* first, char const* last);
    void erase(std::size_t n);
    std::size_t size() const;
    std::size_t capacity() const;
    void reserve(std::size_t n);
    interval_type data() const;
    bool empty() const;

    std::size_t space_left() const;

    char const* raw_data() const
    {
        return m_first;
    }

private:
    char* m_first;
    char* m_last;
    char* m_write_cursor;
    char* m_read_cursor;
	 char* m_read_end;
    bool m_empty;
};

inline buffer::buffer(std::size_t n)
	: m_first((char*)::operator new(n))
	, m_last(m_first + n)
	, m_write_cursor(m_first)
	, m_read_cursor(m_first)
	, m_read_end(m_last)
	, m_empty(true)
{}

inline buffer::~buffer()
{
    ::operator delete (m_first);
}

inline buffer::interval buffer::allocate(std::size_t n)
{
   assert(m_read_cursor <= m_read_end || m_empty);

	if (m_read_cursor < m_write_cursor || m_empty)
	{
	// ..R***W..
		if (m_last - m_write_cursor >= (std::ptrdiff_t)n)
		{
			interval ret(m_write_cursor, m_write_cursor + n);
			m_write_cursor += n;
			m_read_end = m_write_cursor;
			assert(m_read_cursor <= m_read_end);
			if (n) m_empty = false;
			return ret;
		}

		if (m_read_cursor - m_first >= (std::ptrdiff_t)n)
		{
			m_read_end = m_write_cursor;
			interval ret(m_first, m_first + n);
			m_write_cursor = m_first + n;
			assert(m_read_cursor <= m_read_end);
			if (n) m_empty = false;
			return ret;
		}

		reserve(capacity() + n - (m_last - m_write_cursor));
		assert(m_last - m_write_cursor >= (std::ptrdiff_t)n);
		interval ret(m_write_cursor, m_write_cursor + n);
		m_write_cursor += n;
		m_read_end = m_write_cursor;
		if (n) m_empty = false;
		assert(m_read_cursor <= m_read_end);
		return ret;

	}
	//**W...R**
	if (m_read_cursor - m_write_cursor >= (std::ptrdiff_t)n)
	{
		interval ret(m_write_cursor, m_write_cursor + n);
		m_write_cursor += n;
		if (n) m_empty = false;
		return ret;
	}
	reserve(capacity() + n - (m_read_cursor - m_write_cursor));
	assert(m_read_cursor - m_write_cursor >= (std::ptrdiff_t)n);
	interval ret(m_write_cursor, m_write_cursor + n);
	m_write_cursor += n;
	if (n) m_empty = false;
	return ret;
}

inline void buffer::insert(char const* first, char const* last)
{
    std::size_t n = last - first;

    if (space_left() < n)
    {
        reserve(capacity() + n);
    }

    m_empty = false;

    char const* end = (m_last - m_write_cursor) < (std::ptrdiff_t)n ? 
        m_last : m_write_cursor + n;

    std::size_t copied = end - m_write_cursor;
    std::memcpy(m_write_cursor, first, copied);

    m_write_cursor += copied;
	 if (m_write_cursor > m_read_end) m_read_end = m_write_cursor;
    first += copied;
    n -= copied;

    if (n == 0) return;

    if (m_write_cursor == m_last) m_write_cursor = m_first;

    memcpy(m_write_cursor, first, n);
    m_write_cursor += n;
}

inline void buffer::erase(std::size_t n)
{
    assert(!m_empty);
#ifndef NDEBUG
	int prev_size = size();
#endif
	assert(m_read_cursor <= m_read_end);
    m_read_cursor += n;
    if (m_read_cursor > m_read_end)
	 {
        m_read_cursor = m_first + (m_read_cursor - m_read_end);
		  assert(m_read_cursor <= m_write_cursor);
	 }

    m_empty = m_read_cursor == m_write_cursor;

	 assert(prev_size - n == size());
}

inline std::size_t buffer::size() const
{
    // ...R***W.
    if (m_read_cursor < m_write_cursor)
    {
        return m_write_cursor - m_read_cursor;
    }
    // ***W..R*
    else
    {
        if (m_empty) return 0;
        return (m_write_cursor - m_first) + (m_read_end - m_read_cursor);
    }
}

inline std::size_t buffer::capacity() const
{
    return m_last - m_first;
}

inline void buffer::reserve(std::size_t size)
{
    std::size_t n = (std::size_t)(capacity() * 1.f);
    if (n < size) n = size;

    char* buf = (char*)::operator new(n);
    char* old = m_first;

    if (m_read_cursor < m_write_cursor)
    {
    // ...R***W.<>.
        std::memcpy(
            buf + (m_read_cursor - m_first)
          , m_read_cursor
          , m_write_cursor - m_read_cursor
        );

        m_write_cursor = buf + (m_write_cursor - m_first);
        m_read_cursor = buf + (m_read_cursor - m_first);
		  m_read_end = 0;
        m_first = buf;
        m_last = buf + n;
    }
    else
    {
    // **W..<>.R**
        std::size_t skip = n - (m_last - m_first);

        std::memcpy(buf, m_first, m_write_cursor - m_first);
        std::memcpy(
            buf + (m_read_cursor - m_first) + skip
          , m_read_cursor
          , m_last - m_read_cursor
        );

        m_write_cursor = buf + (m_write_cursor - m_first);

        if (!m_empty)
		  {
            m_read_cursor = buf + (m_read_cursor - m_first) + skip;
            m_read_end = buf + (m_read_end - m_first) + skip;
		  }
        else
		  {
            m_read_cursor = m_write_cursor;
				m_read_end = m_write_cursor;
		  }

        m_first = buf;
        m_last = buf + n;
    }

    ::operator delete (old);
}

inline buffer::interval_type buffer::data() const
{
    // ...R***W.
    if (m_read_cursor < m_write_cursor)
    {
        return interval_type(
            const_interval(m_read_cursor, m_write_cursor)
          , const_interval(m_last, m_last)
        );
    }
    // **W...R**
    else
    {
        if (m_read_cursor == m_read_end)
		  {
            return interval_type(
                const_interval(m_first, m_write_cursor)
                , const_interval(m_last, m_last));
		  }
        assert(m_read_cursor <= m_read_end || m_empty);
        return interval_type(
            const_interval(m_read_cursor, m_read_end)
          , const_interval(m_first, m_write_cursor)
        );
    }
}

inline bool buffer::empty() const
{
    return m_empty;
}

inline std::size_t buffer::space_left() const
{
    if (m_empty) return m_last - m_first;

    // ...R***W.
    if (m_read_cursor < m_write_cursor)
    {
        return (m_last - m_write_cursor) + (m_read_cursor - m_first);
    }
    // ***W..R*
    else
    {
        return m_read_cursor - m_write_cursor;
    }
}

}

#endif // LIBTORRENT_BUFFER_HPP

