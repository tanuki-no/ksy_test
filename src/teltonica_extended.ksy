meta:
  id:       teltonica_extended
  endian:   be
 
seq:
  - id:     preamble
    size:   4
    contents: [0x00, 0x00, 0x00, 0x00 ]
    doc:    Преамбула
  
  - id:     len_data
    type:   u4
    doc:    Размер данных начиная с поля Codec ID до поля Number of Data 2

  - id:     data
    type:   data_type
    size:   len_data
    doc:    Полезные данные
  
  - id:     crc16
    type:   u4
    doc:    Код CRC-16

enums:
  codec_type:
    0x08: codec8
    0x8E: codec8_extended
    0x10: codec16
    0x0C: codec12
    0x0D: codec13
    0x0E: codec14
 
  priority_type:
    0:  low
    1:  high
    2:  panic
 
types:

  data_type:
    seq:
    - id:     codec_id
      type:   u1
      enum:   codec_type
      doc:    Тип кодека
  
    - id:     number_of_data_1
      type:   u1
      doc:    Число записей в пакете
 
    - id:     avl_data
      type:   avl_data_type
      doc:    Содержимое пакета

    - id:     number_of_data_2
      type:   u1
      doc:    Число записей в пакете (соответствует значению Number of Data 1)
   
  avl_data_type:
    seq:
      - id:   timestamp
        type: u8
        doc:  Временная метка (64-бит)

      - id:   priority
        type: u1
        enum: priority_type
        doc:  Приоритет

      - id:   gps
        type: gps_data_type
        size: 15
        doc:  Спутниковые параметры

      - id:   io_element
        type: io_element_type
        doc:  Элементы ввода-вывода

  gps_data_type:
    seq:
      - id: longitude
        type: s4
        doc: Долгота

      - id: latitude
        type: s4
        doc: Широта

      - id: altitude
        type: s2
        doc: Высота над уровнем моря

      - id: angle
        type: u2
        doc: Азимут в градусах по часовой стрелке

      - id:   satellites
        type: u1
        doc:  Количество видимых спутников

      - id:   speed
        type: u2
        doc:  Скорость в км/ч

  io_element_type:
    seq:
      - id:   event_id
        type: u2
        doc:  Event IO ID – if data is acquired on event – this field defines which IO property has changed and generated an event. If data cause is not event – the value is 0.

      - id:   total_io
        type: u2
        doc:  Количество записей N = N1 + N2 + N4 + N8 + NX

      - id:   num_n1_data
        type: u2
        doc:  Количество записей с однобайтовым значением

      - id:   n1_data
        type: n1_data_type
        repeat: expr
        repeat-expr: num_n1_data
        doc:  Записи с однобайтовым значением

      - id:   num_n2_data
        type: u2
        doc:  Количество записей с двухбайтовым значением

      - id:   n2_data
        type: n2_data_type
        repeat: expr
        repeat-expr: num_n2_data
        doc:  Записи с двухбайтовым значением

      - id:   num_n4_data
        type: u2
        doc:  Количество записей с четырёхбайтовым значением

      - id:   n4_data
        type: n4_data_type
        repeat: expr
        repeat-expr: num_n4_data
        doc:  Записи с четырёхбайтовым значением

      - id:   num_n8_data
        type: u2
        doc:  Количество записей с восьмибайтовым значением

      - id:   n8_data
        type: n8_data_type
        repeat: expr
        repeat-expr: num_n8_data
        doc:  Записи с восьмибайтовым значением

      - id:   num_nx_data
        type: u2
        doc:  Количество записей с переменным значением

      - id:   nx_data
        type: nx_data_type
        repeat: expr
        repeat-expr: num_nx_data
        doc:  Записи с переменным значением

  n1_data_type:
    seq:
      - id:   key
        type: u2
        doc:  Ключ
 
      - id:   value
        type: u1
        doc:  Значение

  n2_data_type:
    seq:
      - id:   key
        type: u2
        doc:  Ключ
 
      - id:   value
        type: u2
        doc:  Значение

  n4_data_type:
    seq:
      - id:   key
        type: u2
        doc:  Ключ
 
      - id:   value
        type: u4
        doc:  Значение

  n8_data_type:
    seq:
      - id:   key
        type: u2
        doc:  Ключ
 
      - id:   value
        type: u8
        doc:  Значение

  nx_data_type:
    seq:
      - id:   key
        type: u2
        doc:  Ключ
 
      - id:   len_value
        type: u2
        doc:  Размер
      
